<!-- <h2 align=center>Week 05</h2>

<h1 align=center>Animation / The <code>Entity</code> Class</h1>

<h3 align=center>III Wyvern Moon, Imperial Year MMXXV</h3>

<p align=center><strong>Songs of the day</strong>:</p>
<p align=center><em><a href="https://youtu.be/PC2HkP5gR2g?si=xGn1ra28ArIvUEUV"><strong><u>I'm Not In Love</u></strong></a> by 10cc (1972)</em> recommended by Alaya Chowdhury</p>
<p align=center><em><a href="https://youtu.be/v7GMG1aLyPw?si=XxR1FFhmr-1n7L3g"><strong><u>Sonne</u></strong></a> by Rammstein (2001)</em> recommended by Blessing Yeboah</p>

---

## Sections

1. [**Texture Atlases and Sprite Sheets**](#1)
2. [**Isolating Sprites In A Sprite Atlas**](#2)
3. [**Animation**](#3)
    1. [**Animating A Single Row From The Atlas**](#3-1)
    2. [**Animating Multiple Rows From The Atlas**](#3-2)
3. [**The `Entity` Class: _Making A Game Object_**](#4)
    1. [**The `Entity` Class Attributes**](#4-1)
        1. [**The Familiar**](#4-1-1)
        2. [**The New**](#4-1-2)
    2. [**The `Entity` Class Methods**](#4-2)
        1. [**Constructors**](#4-2-1)
        2. [**`update(float deltaTime)` and `render()`**](#4-2-2)

---

<a id="1"></a>

## Texture Atlases and Sprite Sheets

Using only the raw frame‑to‑frame delta time makes physics, animation, and game logic run at whatever speed the rendering loop happens to achieve, which can vary wildly across hardware, load spikes, or V‑sync changes. By accumulating elapsed time and then stepping the simulation forward in constant, predefined increments (the /_fixed timestep_), the game’s core mechanics stay deterministic and stable: collisions resolve the same way each frame, physics integrators remain numerically well‑behaved, and replay/network synchronization become far easier. The delta time is still needed to know _how much_ real time has passed, but the accumulator guarantees that the simulation advances in uniform chunks, while any leftover fraction is carried over to the next frame so no time is lost.

The steps to do this are as follows:

1. Measure elapsed wall‑clock time
    ```c++
    float ticks = (float) GetTime();          // current time in seconds (or ms)
    float deltaTime = ticks - gPreviousTicks; // time since last frame
    gPreviousTicks = ticks;                   // store for next iteration
    ```
    `deltaTime` now holds the raw frame‑to‑frame duration.

2. Add any previously unprocessed remainder
    ```c++
    deltaTime += gTimeAccumulator;
    ```
    `gTimeAccumulator` stores the fraction of time that was too small to form a full fixed step during the previous frame.

3. Check whether we have enough time for even one fixed step
    ```c++
    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime; // keep the leftover for next frame
        return;                       // skip simulation this frame
    }
    ```
    If the accumulated time is less than the desired step size, we bail out early, preserving the leftover.

4. Consume as many whole fixed steps as possible

    ```c++
    while (deltaTime >= FIXED_TIMESTEP)
    {
        gProtag->update(FIXED_TIMESTEP);               // advance player logic
        for (int i = 0; i < NUMBER_OF_TILES; i++)      // advance all tiles
            gTiles[i].update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;                  // remove the consumed slice
    }
    ```
    - Each iteration represents one deterministic simulation tick (`FIXED_TIMESTEP`).
    - All game objects (the protagonist and each tile) are updated with exactly the same time step, ensuring consistent physics and gameplay regardless of frame rate.
    - After processing, deltaTime holds any remaining fraction that didn’t fit another full step.

5. Store the leftover for the next frame
    (Implicitly done because `gTimeAccumulator` isn’t overwritten after the loop.)
    The residual `deltaTime` (now < `FIXED_TIMESTEP`) will be added to the next frame’s raw delta time at step 2, guaranteeing that no time is ever discarded.

The game runs its logical simulation at a steady, predictable cadence while still respecting the actual passage of real time, yielding smoother physics, reproducible behavior, and easier networking or replay support.

“I still don’t get why this is any different from delta time.”

Delta time is simply “how much real time elapsed since the last frame.” If you feed that raw value straight into your physics or animation code, each update runs for a different amount of simulated time. Imagine two consecutive frames where the delta times are 0.016 s (60 fps) and 0.033 s (30 fps). A physics integrator that receives those numbers will move objects farther in the second frame, which can cause jittery motion, unstable collision responses, and non‑deterministic results—especially when the frame‑rate swings dramatically.

A fixed‑timestep takes the same delta‑time information but normalizes it: you accumulate the elapsed time and then repeatedly consume it in equal, pre‑chosen slices (e.g., 0.016 s). The simulation therefore sees a constant step size every time it updates, regardless of how irregular the rendering loop is. The only place the raw delta time still matters is in the accumulator, which guarantees that no time is lost; any leftover fraction rolls over to the next frame. In short, delta time tells you how much time passed, while a fixed‑timestep tells the simulation how to apply that time in a stable, repeatable way.

“Could you give a concrete example as to when this would be useful?”

Consider a 2‑D platformer with precise pixel‑perfect collision detection and a physics engine that integrates velocity → position using a simple Euler step:

position += velocity * dt;
If the game runs at a steady 60 fps, dt ≈ 0.016 s, and everything feels smooth. Now imagine the player pauses the game, opens a system dialog, or the CPU spikes because of background work, causing a frame to take 120 ms (dt ≈ 0.12 s). Feeding that large dt into the Euler step will push the character far beyond walls, miss collision checks, and possibly tunnel through thin platforms entirely. The result is a sudden “teleport” or the character getting stuck.

With a fixed‑timestep of 0.016 s, the same 120 ms of real time is broken into seven discrete updates:

120 ms / 16 ms ≈ 7 full steps (with a tiny remainder)
Each step moves the character only a small, predictable distance and performs collision checks at every intermediate position. Even if the frame took longer, the physics behaves exactly as if the game had been running at 60 fps for those seven ticks, preserving stability and determinism.

Other practical scenarios where a fixed timestep shines:

Situation	Why a fixed step helps
Networked multiplayer – synchronizing state across clients	Deterministic simulation means the same inputs produce identical outcomes on every machine, simplifying lock‑step or rollback netcode.
Replay / save‑state systems – reproducing past gameplay	Replaying a recorded sequence of inputs yields the exact same world evolution when the simulation runs with a constant step size.
Physics‑heavy games – ragdolls, particle systems	Numerical integrators (Verlet, RK4, etc.) are stable only when the step size stays within a known bound; varying dt can cause explosions or jitter.
Variable rendering rates – VR or high‑refresh monitors	Rendering may run at 90 Hz while the physics only needs 60 Hz; the accumulator decouples the two loops cleanly.
In all these cases, the fixed‑timestep isolates the logic from the rendering timing, delivering consistent, predictable behavior even when the visual frame rate fluctuates. -->