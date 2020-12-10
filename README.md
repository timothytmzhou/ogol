Ogol is a clone of the [Logo programming language](https://el.media.mit.edu/logo-foundation/what_is_logo/logo_primer.html), a DSL for drawing [turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics), which are "vector graphics using a relative cursor (the "turtle") upon a Cartesian plane" (Wikiepedia).

**Language**
Unlike logo itself, Ogol's syntax is scheme-like, making use of S-expressions. For instance:
```
(print "hello world")
```
Is how one prints "hello world" to the console. The main point of Ogol is drawing vector graphics to an onscreen GUI. In addition to basic printing and arithmetic operations, a few commands are supported:
```
(forward 30)
```
Moves the turtle 30 pixels forward, leaving a straight line.
```
(rotate 30)
```
Turns the angle of the turtle 30 degrees counter-clockwise. 
```
(color "red")
```
Changes the color of the turtle.
**Installation**
Simply clone from [the repo](https://github.com/uiuc-fa20-cs126/final-project-stackdynamic) and run `ogol-lang-app`.
