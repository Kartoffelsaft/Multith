# Multith

I might start working on this project again as I believe I found the source of what was causing the issue. I'll keep what's below because it's still an interesting read

___

this is a project heavily focused on multithreading (hence the name "multith") that I have now nearly abandoned. It had (has?) potential, but I would need a much better understanding of how to work with threads and avoid undefined behavior.

## Why has work stopped on this?

TL;DR: there was a bug that I had been losing hairs over for a month. I'll go into technical details below, but keep in mind that it is really involved.

I was working on adding sprite animations, but once I finally got a working build going I was just left with a blank screen. I was expecting a bug like that to occur (because they always do with a first feature build). Problem is, I kept reverting small changes without the bug going away. Eventually I just did a hard reset to the previous working build, and it was working as expected.

Then I made a tiny change: I added an ```int``` to the ```WindowHandler``` class. Only that. Never used it, never wrote to it, nothing. The bug appeared. At this point I knew something was _really_ broken.

After several hours of debugging I found that the direct cause of the bug whas that the ```TickCoordinator``` was attempting to access a mutex, but the mutex was locked. No other thread was notified of the next game tick, and so they did nothing. I found this incredibly confusing because no other thread had a lock on that mutex. There was no reason for any of them to when they were all idling.

Using gdb, I tried to read the data sitting in the mutex for myself. Of course, when the mutex is initialized it is unlocked. And before the ```TickCoordinator``` thread was given any reference to it, it remained unlocked. As soon asthe ```TickCoordinator``` had access to it, though, it read it as being locked by another thread. Keep in mind this is from the perspective of the ```TickCoordinator```. Every other thread with reference to it knew it was unlocked.

I figured I'd use gdb to find the mutex's location in memory, and use that to see what it said was there. That's how I found out that the ```TickCordinator``` thread thought it was in a slightly different place in memory than it actually was; It was offset by ```sizeof(int)```. To test if this was related in any way to the original inclusion of an ```int```, I replaced it with a ```long double```, and sure enough the offset was larger.

So it's probably undefined behavior.
