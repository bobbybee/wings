# WINGS
_An OS to let you fly free_

WINGS was backronymed "WINGS Is Not The GNU System", in reference to the ideals of the GNU system -- and how this is not a *nix!

# Architecture

WINGS is built around a Lisp dialect. Why? Because Lisp's are beautiful. And, with some modification to the implementation, lend themselves quite nicely to operating system development.

WINGS has its own kernel that is designed to support the userspace Lisp system efficiently. Garbage collection and the like are planned to be implemented in kernel-space. Whereas a POSIX kernel has a C paradigm built into the kernel, WINGS has Lisp.

While this project might have practical uses, it's largely being developed for my own educational benefit. Therefore, I'm trying to minimize porting existing, third-party code. Notably, this means I'm developing a compiler alongside the kernel (and the userspace).

# Why?

Because OS dev is fun. Because OS dev is educational. And most of all -- because Lisp is awesome.

# Current State

Please ignore this. It barely has working keyboard input, and it's compiler has no output yet. Maybe soon something will work out.
