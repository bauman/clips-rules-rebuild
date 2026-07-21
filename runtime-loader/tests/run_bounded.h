#ifndef RUNTIME_LOADER_RUN_BOUNDED_H
#define RUNTIME_LOADER_RUN_BOUNDED_H

#include <stdio.h>
#include "clips.h"

/*
 * run_bounded -- Run the agenda with a HARD CAP, instead of Run(env, -1).
 *
 * WHY: the loader's fact protocol is a small rule loop (loadlib / unloadlib plus
 * the error rules), and a defect can make it re-fire forever. F8 did exactly
 * that: UnLoader left `out` unset, the rule wrote garbage into the `loaded` slot,
 * and the loop span. With Run(env, -1) that is an infinite hang -- the test never
 * fails, it just burns CI minutes until a timeout kills it. With a cap it fails
 * fast and says how many rules fired.
 *
 * MEASURED firing counts for the loader's rules (so the bounds below aren't
 * folklore -- these were observed, not guessed):
 *
 *   successful load or unload ............... 1
 *   two load facts asserted together ........ 2
 *   any FAILURE path (-3/-4/-6/-32 etc.) .... 3
 *   unload-in-use -> reload bounce .......... 4
 *
 * A failure path is 3, not 2, because the error rule's `(modify ?d (error "..."))`
 * re-asserts the fact and so re-activates its own pattern; the second modify writes
 * an identical value, which CLIPS treats as no change, and it stops there. The
 * reload bounce is 4: unloadlib -> unloader-unable-to-delete (which re-arms the
 * fact for load) -> loadlib -> loader-already-defined.
 *
 * So callers pass cap=10 / expect_max=6 for ordinary sites (comfortably above the
 * observed 3) and a larger pair for the reload bounce. A genuine runaway is
 * unbounded, so it hits `cap` and trips `expect_max` regardless of the headroom.
 *
 *   cap        -- hard limit passed to Run(); bounds the work no matter what.
 *   expect_max -- assertion: more than this many firings is a failure.
 *   what       -- label for the diagnostic.
 *
 * Returns the number of rules fired, or -1 if it exceeded expect_max (the caller
 * should treat that as a test failure). Note a runaway is caught either way: Run
 * stops at `cap`, and `cap` is chosen above `expect_max` so the excess is visible.
 *
 * NOTE: this is for TESTS. The runtime-clips CLI (app/main.c) deliberately keeps
 * Run(env, -1) -- there, many rule firings are the user's legitimate program.
 */
static int run_bounded(Environment* env, long long cap, int expect_max, const char* what)
{
   int fired = (int)Run(env, cap);
   if (fired > expect_max)
     {
      fprintf(stderr, "FAIL: %s fired %d rules, expected at most %d (runaway rule loop?)\n",
              what, fired, expect_max);
      return -1;
     }
   return fired;
}

#endif
