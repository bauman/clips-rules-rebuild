#include <atomic>
#include <cstdio>
#include <thread>
#include <vector>

#include "plugin_names.h"

/* Declared here (extern "C") rather than via dispatcher.h so this C++ test links
   against the C-compiled definitions. PerformLoading operates purely on the
   process-global tables + dlopen/dlsym -- no Environment needed -- so we can
   hammer it directly from many threads. loader_*_count read the tables. */
extern "C" {
   int  PerformLoading(const char* library, const char* function);
   long loader_library_count(void);
   long loader_function_count(void);
}

/*
 * F3 regression: concurrent first-loads of the same library must load it ONCE.
 * PerformLoading checks the table, loads outside the lock, then inserts; without
 * the double-checked insert two racing threads both dlopen and both HASH_ADD the
 * same key, producing duplicate/leaked entries. Many threads load the same
 * library+function simultaneously; afterward there must be exactly one entry each.
 */
int main()
{
   const int N = 32;
   std::atomic<bool> go(false);
   std::atomic<int> successes(0);
   std::vector<std::thread> threads;

   for (int i = 0; i < N; i++)
     {
      threads.emplace_back([&]() {
         while (!go.load(std::memory_order_acquire)) { /* spin so all threads start together */ }
         if (PerformLoading(CUBE_LIB, "Cube") == 1)
           { successes.fetch_add(1, std::memory_order_relaxed); }
      });
     }
   go.store(true, std::memory_order_release);   /* release the herd */
   for (auto& t : threads) { t.join(); }

   int failures = 0;
   long libs  = loader_library_count();
   long funcs = loader_function_count();
   std::printf("after %d concurrent loads: successes=%d library_count=%ld function_count=%ld\n",
               N, successes.load(), libs, funcs);

   if (successes.load() != N) { std::fprintf(stderr, "FAIL: not all %d loads succeeded\n", N); failures++; }
   if (libs  != 1) { std::fprintf(stderr, "FAIL: library_count=%ld, expected 1 (load-once violated)\n", libs); failures++; }
   if (funcs != 1) { std::fprintf(stderr, "FAIL: function_count=%ld, expected 1 (load-once violated)\n", funcs); failures++; }

   if (failures) { return 1; }
   std::printf("F3 concurrent load-once: OK\n");
   return 0;
}
