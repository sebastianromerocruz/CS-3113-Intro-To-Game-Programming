<h2 align=center>Week 01</h2>

<h1 align=center>Hello, Raylib</h1>

<h3 align=center>1 Red Wolf Moon, Imperial Year MMXXIV</h3>

<p align=center><strong><em>Song of the day</strong>: <a href="https://www.youtube.com/watch?v=phT2MJAn1KY&ab_channel=TOMORROWXTOGETHER-Topic"><strong><u>APT</u></strong></a> by ROSÉ & Bruno Mars (2024).</em></p>

---

## Sections

1. [**What Is Game Programming?**](#1)
2. [**Why raylib?**](#2)
3. [**Hello, Raylib!**](#3)
    1. [**`main`**](#3-1)

---

<a id="1"></a>

## What Is Game Programming?

Let's start by addressing _the_ single most common question I get whenever anybody asks me about this class: why aren't we using Unity / Unreal / literally any other industry-standard game engine that's freely-available to us? Wouldn't _that_ be the best way to jump start a career in games?

Yes and no. It is true that a lot of video game developers get their careers started with pre-built engines. The whole appeal of using them is that you don't have to worry about the minutiae that comes with rendering pixels on the screen and making them interactive. At the risk of sounding a little patronising (this isn't my intention—I've programmed a lot in Unity), you could call this way of learning "game dev with training wheels". And there's nothing wrong with that! A lot of the times, developers have a strong vision and whichever tool help them achieve that goal most efficiently is going to be the most obvious choice. Honestly, as long as we're getting good games out of it, who cares? 

So, why aren't _we_ doing that?

Consider the name of this course: "Introduction to Game Programming." How would you define game programming? Or, put another way, what is a game developer responsible for? It's not a straightforward question with a straightforward answer, especially with tools like Unity and Unreal. If I were to hazard an answer, it would be the following:

1. The implementation of the game's interactivity.
2. The implementation of the game's graphics.
3. The implementation of the game's physics, if any.

The last two of these are especially important, in my opinion, and a lot more complex than you may think. We tend to take graphics for granted as citizens of the 21st century, since we see them everywhere, all the time. We're used a drag-and-drop model of interacting with images where we don't really need to even think about the resources necessary for the liquid crystals under our screens to show us what we want where we want. Taking into account that, under the hood, all of this ends up being broken into machine code anyway, there's quite a bit to this process that we're (by design) simply not thinking about.

Physics, too, is a more loaded topic than meets the eye. When we say that a game has very immersive movement or control, what _exactly_ are we saying? Generally speaking, we say this when something feels _realistic_—that is, akin to the laws of physics that we interact with in the real world. It feels familiar to us, so it makes us forget, for a little bit, that we're playing a game. Evoking this feeling is not easy, because mechanics are extremely complicated. Simulating the way a body moves through space, complete with its reactions to outside stimuli (like air resistance, etc) is really difficult! We don't think about it, because we literally live it, but when it comes time to tell something digital to act the same way, we're suddenly talking about something magnitudes more complex.

The reason why I choose not to utilise pre-built engines in this class is because they tend to take the responsibility for these two things away from the developer—or at least abstract them away so much to the point of triviality. Of course, it's not as if you _can't_ ask for finer control in pre-built engines—you can (especially in Unreal), but at that point, it's almost as if you were working "against the grain" of these pieces of software. Meaning: why are you even using Unity if you're just going to reprogram the way Unity handles things? That kind of thing.

So, what does this amount to? By choosing not to use a pre-built engine, we are effectively choosing to _build an engine ourselves_. That's right: from the ground up, we will be using a cute little library call **raylib** to build our own custom game engine, capable of rendering graphics the way _we_ want it to, handle user input the way _we_ want it to, and simulate physics the way _we_ want it to. The benefits of this approach, in my opinion, far outweigh any "handicap" we might have for not using a pre-built engine:

1. You get lots of programming practice doing something you can call your own.
2. You can immediately expand your résumé with any of the games that you will program this semester, stating (correctly) that it was doing in your own custom engine.
3. Most [**professional developers**](https://gist.github.com/raysan5/909dc6cf33ed40223eb0dfe625c0de74) use their own custom engines, which they of course build themselves.
4. After this class, picking up Unity and/or Unreal will be a piece of cake. (Getting good at them? Another story.)

If you agree with my reasoning, or at least if you're not going to drop the class after today, then I welcome you. I can't wait to see what you make.

<br>

<a id="2"></a>

## Why raylib?

The better-informed amongst you may be aware that I used to teach this course using an [**old, janky version of a library called OpenGL**](https://github.com/sebastianromerocruz/CS3113-intro-to-game-programming/tree/main?tab=readme-ov-file#cs3113-introduction-to-game-programming). We actually will still be using OpenGL, but in a slight different, more controlled way. [**OpenGL**](https://www.opengl.org/) is a quite famous library that interacts directly with your graphics card to create hi-fi graphics with much smaller overhead than, say, Unity or even Unreal. The particulars of why I'm switching out of that model are not important, but the gist is that as students' started to get newer, compatibility issues basically became the norm, and it was really messing with the focus of the class. Basically, more time was being spent figuring out why the setup didn't work than actually working on the game themselves.

So, a former student recommended [**raylib**](#https://www.raylib.com/index.html) which, in their own words:

> _...is a programming library to enjoy videogames programming; no fancy interface, no visual helpers, no gui tools or editors... just coding in pure spartan-programmers way._
> 
> — Official raylib website.

<a id="fg-1"></a>

<p align=center>
    <img src="https://raw.githubusercontent.com/raysan5/raylib.com/master/images/raylib_architecture_v5.5.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure I</strong>: raylib's entire architecture (<a href="https://github.com/raysan5/raylib/wiki/raylib-architecture"><strong>source</strong></a>).
    </sub>
</p>

As you can see, raylib itself is built on OpenGL, so we are still getting a pretty fine level of control over our machines, just with more friendly programmatic interface. Other things that I like about it are that:

- It's a breeze to set up.
- It is [**highly-modular**](https://github.com/raysan5/raylib/wiki/raylib-architecture). We like that.
- It is open-source. We _love_ that.
- It's ported to [**every language under the sun**](https://github.com/raysan5/raylib/blob/master/BINDINGS.md#raylib-bindings-and-wrappers). We're really only using the C version because C/C++ tends to be the standard in the industry.

Overall, while there are some things I wish it did differently / closer to how raw OpenGL does it, it seems to be a really small but powerful library—and more than enough for what we will be covering this semester.

<br>

<a id="3"></a>

## Hello, Raylib!

To get started with the library, let's analyse the code necessary to display an off-white screen using raylib and break it up part-by-part:

<a id="cb-1"></a>

```cpp
#include "raylib.h"

// Enums
enum AppStatus { TERMINATED, RUNNING };

// Global Constants
constexpr int SCREEN_WIDTH  = 800,
              SCREEN_HEIGHT = 450,
              FPS           = 60;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello raylib!");

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() {}

void render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
}

void shutdown() 
{ 
    CloseWindow(); // Close window and OpenGL context
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    return 0;
}
```

<p align=center>
    <sub>
        <strong>Code Block I</strong>: The contents of this week's <a href="main.cpp"><strong>source code</strong></a>.
    </sub>
</p>

To run the following code (assuming you have its [**corresponding `makefile`**](makefile) in the same folder), simply run the following command in your terminal/command line:

```bash
make run
```

And voilà!

<a id="fg-2"></a>

<p align=center>
    <img src="assets/hello-raylib.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure II</strong>: Fascinating, I know.
    </sub>
</p>

<a id="3-1"></a>

### `main`

As with any program, we should look at its driver function if we want to get a good idea of how it works on a high-level. In the case of video games, this tends to take the shape of something called a **game loop**:

<a id="cb-2"></a>

```cpp
int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    return 0;
}
```

<p align=center>
    <sub>
        <strong>Code Block II</strong>: Our invariable `main` function. With maybe a single exception this semester, this function should/will never change.
    </sub>
</p>

[**Micheal Stutz**](https://en.wikipedia.org/wiki/Video_game_programming#Game_structure) gives us a slightly more specific, pseudo-code definition:

```
while (user does not exit)
    check for user input
    run AI
    move enemies
    resolve collisions
    draw graphics
    play sounds
end while
```

Essentially, what we're seeing here is that, in order to run a game, you must:
1. **Initialise it**, i.e., setting up the screen, clearing the memory buffers, etc..
2. Until the user quits, **run it**. This involves:
    1. **Getting input from the user**, which may come from a keyboard, a mouse, a controller, etc.. We then _record_ this input somewhere to use it later (if there was any input at all).
    2. **Process the game's current frame**, which is a catch-all way of saying: "make everything do what it's supposed to do under the current circumstances". The player pressed `A` to jump in step 2.1? It's time to make the character jump. Did two enemies collide, causing them to walk in opposite directions? Time to change their direction vectors. So on and so forth. In essence, most of your game logic will go in here.
    3. Whatever it is that happened this frame **render/draw it on the screen**. This usually involves clearing the previous frame and asking the GPU to draw the new one, complete with whichever new positions/rotations/scales we ended up with after step 2.2.

This is important, if only because you will see this pattern again and again in every game development environment you're in. What's even more important right now, though, is to remember to _not mix things up_. In other words, make sure that _all_ user input is handled by the `processInput` function, _all_ state updates happen in `update`, and _all_ drawing happens in `render`. This way we can keep everything nice a modularised while keeping up with the industry's best practices.

If you've never seen an [**enum**](https://en.wikipedia.org/wiki/Enumerated_type) before, the following might be a little confusing:

```c++
enum AppStatus { TERMINATED, RUNNING };

AppStatus gAppStatus = RUNNING;

void main()
{
    while (gAppStatus == RUNNING) 
    {
        // ...
    }
}
```

Behind the hood, the values of enums are actually integers, starting from 0 and incrementing by a step of 1. This means that if I defined the following enum:

```c++
enum Day { MON, TUES, WED, THUR, FRI, SAT, SUN };
```

`MON` actually has a value of `0`, `TUES` has a value of `1`, `WED` of `2`, and so on. You can see this in the following screenshot:

<a id="fg-3"></a>

<p align=center>
    <img src="assets/enums.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure III</strong>: Enumerators under the hood.
    </sub>
</p>

In general, they are considered to be a better way of handling logic than booleans are, as they are easily readable and are not limited to only two values.

<a id="3-2"></a>

## `initialise`

The first function we find in our `main` is that of `initialise`. As previously alluded to, this function takes care of a lot of the "housecleaning" necessary for your game to run smoothly. In general, this will involve the following:

1. **Initialising a window**. I mean this literally, too. Computers don't just generate windows just because we click on icons. We have to _tell_ our operating system, and our graphics card by extension, to dedicate a portion our the screen to what we want to display. In raylib, this is relatively simple, using the following line:
    ```cpp
    InitWindow(
        SCREEN_WIDTH,   // in pixels
        SCREEN_HEIGHT,  // in pixels
        "Hello raylib!" // text shown on the title of the window
    );
    ```
    Keep in mind that [**1 pixel is equivalent to about 26.5 mm**](https://www.unitconverters.net/typography/pixel-x-to-centimeter.htm).
2. **Initialising the game's camera**.