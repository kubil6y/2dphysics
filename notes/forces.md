## Forces

- A particle will **accelerate** based on the **forces** that are acting on it.
- Forces may come from different sources depending on the kind of simulation. It can be _gravity, wind, magnetism_ etc. Or it can be a force between particies, such as attraction or repulsion.
- For each frame, we are interested in the final sum of all forces (net force) that is being applied to the particle.
- The **mass** of an object determines how difficult it is to accelerate that object once a force is applied to it.

Note: Kinematics: velocity, acceleration but no forces...

---

## Drag Force

- Drag is a **resistive** force acting in the **opposite** direction of the relative motion of any object moving with respect to a surrounding **fluid**.
- Unlike other resistive forces (such as dry friction, which are nearly independent of velocity), the drag force **depends on velocity**.

```
Drag Force (Fd) = 0.5 * Kd * A * ρ * ||v||^2 * -vdir

Fd = Drag force
Kd = Drag coefficient (dimensionless)
A = Cross-sectional area (in square meters)
ρ = Density of the fluid (in kilograms per cubic meter)
v = Velocity of the object relative to the fluid (in meters per second)
vdir = Negative direction of unit vector

Simplified for game dev:

Drag Force (Fd) = k * ||v||^2 * -vdir
k = constant
```

---
