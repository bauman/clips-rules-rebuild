#include <atomic>
#include <cstdio>
#include <thread>
#include <vector>

#include "plugin_names.h"

/* Declared extern "C" (not via dispatcher.h) so this C++ test links the
   C-compiled definitions -- same approach as concurrent_load.cpp. PerformLoading
   works purely on the process-global tables + dlopen/dlsym (no Environment), so we
   can hammer it from many threads. teardown_dispatcher resets those tables (and the
   lock) between rounds so each round re-opens the race window. */
extern "C" {
   int  PerformLoading(const char* library, const char* function);
   long loader_function_count(void);
   long loader_library_count(void);
   bool teardown_dispatcher(void);
}

/*
 * F4 race-hardening regression: two libraries (cube, cube2) built from the same
 * source both export "Cube". If threads concurrently load "Cube" from DIFFERENT
 * libraries, the unique-name constraint must still hold: exactly ONE library wins
 * the name (all its requesters get 1) and every requester of the other library is
 * refused (-4). The bug this guards: a thread that raced past the up-front
 * uniqueness check used to find the winner's entry at the final success check and
 * return 1 -- reporting success while it actually requested the OTHER library, so
 * its deffunction would silently dispatch into the wrong code. The fix re-checks
 * the owning library at the final check; a loser now gets -4, never a misrouted 1.
 *
 * Timing-dependent like concurrent_load.cpp: when a round happens not to hit the
 * race, the up-front check refuses the loser anyway, so the invariant still holds
 * and the round passes. Many rounds make the race overwhelmingly likely to occur;
 * with the fix reverted, any round that hits it fails.
 */

int main()
{
   const int ROUNDS = 128;
   const int PER_LIB = 8;               /* threads per library per round */
   const char* libs[2] = { CUBE_LIB, CUBE2_LIB };

   int failures = 0;

   for (int r = 0; r < ROUNDS && failures == 0; r++)
     {
      std::atomic<bool> go(false);
      std::atomic<int> succ[2] = { {0}, {0} };      /* result == 1  per lib */
      std::atomic<int> refused[2] = { {0}, {0} };    /* result == -4 per lib */
      std::atomic<int> other(0);                      /* any other result code */
      std::vector<std::thread> threads;

      for (int lib = 0; lib < 2; lib++)
        {
         for (int i = 0; i < PER_LIB; i++)
           {
            threads.emplace_back([&, lib]() {
               while (!go.load(std::memory_order_acquire)) { /* start together */ }
               int rc = PerformLoading(libs[lib], "Cube");
               if (rc == 1)       { succ[lib].fetch_add(1, std::memory_order_relaxed); }
               else if (rc == -4) { refused[lib].fetch_add(1, std::memory_order_relaxed); }
               else               { other.fetch_add(1, std::memory_order_relaxed); }
            });
           }
        }
      go.store(true, std::memory_order_release);
      for (auto& t : threads) { t.join(); }

      /* exactly one library must own the name */
      long funcs = loader_function_count();
      bool won[2] = { succ[0].load() > 0, succ[1].load() > 0 };

      if (other.load() != 0)
        { std::fprintf(stderr, "round %d FAIL: %d unexpected result code(s)\n", r, other.load()); failures++; }
      if (funcs != 1)
        { std::fprintf(stderr, "round %d FAIL: function_count=%ld, expected 1\n", r, funcs); failures++; }
      if (won[0] == won[1])
        { std::fprintf(stderr, "round %d FAIL: expected exactly one winner (won0=%d won1=%d)\n", r, won[0], won[1]); failures++; }
      else
        {
         int win = won[0] ? 0 : 1;
         int lose = 1 - win;
         /* winner: every requester succeeded, none refused */
         if (succ[win].load() != PER_LIB || refused[win].load() != 0)
           { std::fprintf(stderr, "round %d FAIL: winner lib %d succ=%d refused=%d (want %d/0)\n",
                          r, win, succ[win].load(), refused[win].load(), PER_LIB); failures++; }
         /* loser: every requester refused with -4, none misrouted to success */
         if (succ[lose].load() != 0 || refused[lose].load() != PER_LIB)
           { std::fprintf(stderr, "round %d FAIL: loser lib %d succ=%d refused=%d (want 0/%d) -- misroute?\n",
                          r, lose, succ[lose].load(), refused[lose].load(), PER_LIB); failures++; }
        }

      /* reset the loader so the next round races from an empty table */
      if (!teardown_dispatcher())
        { std::fprintf(stderr, "round %d FAIL: teardown_dispatcher returned false\n", r); failures++; }
     }

   if (failures) { return 1; }
   std::printf("F4 concurrent name-collision (one winner, loser refused): OK\n");
   return 0;
}
