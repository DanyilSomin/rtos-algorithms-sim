# rtos-algorithms-sim
Sandbox for testing different algorithms for finding free place on the array. Project contains several algorithms for finding free process place in the array of processes (see strategy*.h files) and settings (settings.h) where user can easy change all sandbox configuration such as vectors length, time process alive, creation period.

# Build
Use cmake .<br>
For example on unix like systems:<br>
$ cmake .<br>
$ make .<br><br>
Or just call cmake . and open the .sln in case of Visual Studio.

# Write own algorithm
To write own algorithm see other algorithm as example, inherit from Strategy interface (strategy.h) and add appropriate strategy in main().
