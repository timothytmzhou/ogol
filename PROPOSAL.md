
This project will be a clone/derrivative of the [Logo programming language](https://el.media.mit.edu/logo-foundation/what_is_logo/logo_primer.html), a DSL for drawing [turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics), which are "vector graphics using a relative cursor (the "turtle") upon a Cartesian plane" (Wikiepedia). 

**The Logo Programming Language**
In Logo, the turtle can move forward, rotate, and change its pen's color, width, etc. For example, the following Logo code:
`repeat 4 [forward 50 right 90]`
will draw a square. Logo is a Lisp with very simple syntax: there is support for console output using `print`, basic arithemtic operations (unlike most Lisps, Logo does not use S-expressions and adopts conventional infix notation),  procedures/functions, conditionals, and so on. Intrestingly, even though the turtle is very limited in its capabilities, stunningly complex figures can be easily created. Abelson even co-wrote a [college-level text](https://mitpress.mit.edu/books/turtle-geometry) on Turtle Geometry, which gives a formal mathematical treatement of turtle graphics. Here is another example, a procedure which draws a spiral:
```
to spiral :size :angle
if :size > 100 [stop]
forward :size
right :angle
spiral :size + 2 :angle
end
```
**Project Description**
I plan on writing an interpreter for a "Logo-like" language which modifies the syntax slightly. The end product will be a GUI which can read in a text file with code, lex/parse it, and then draw the output to the screen. With regards to background knowledge, I have written a small interpreter for a toy language before, so I am relatively familiar with basic concepts like parsing algorithms, abstract syntax trees, etc. As to why I want to do this project, I think that the way in which it integrates the GUI requirement is novel and interesting, combining aspects of two normally disparate fields, programming languages and computer graphics. Of course, writing a programming language and getting to see it run is also quite fun.

**Very Rough Timeline**
Week 1:

 - Complete language design/specification
 -  Parsing infrastructure
 - Implementation of basic features like arithmetic and `print`
 - Testing infrastructure
 -  Rendering turtle and its path to screen and implementation of `right` and `forward`

Week 2:
 - Implementation of control flow: conditionals, `repeat`, custom procedures, etc.
 - Procedures for changing pen color, thickness, etc.
 - Procedures relating to turtle rendering/movement (showturtle, hideturtle, home, etc.)

Week 3:
- Code cleanup
- Add useful/interesting built-ins (lists, maps, filters, etc.)
- Implement some of the stretch goals listed below

**Stretch Goals**
 - Small standard library
 - Error handling for scripts
 - Additional data structures, features, or extensions of the language
 