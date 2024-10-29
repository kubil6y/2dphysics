# Forces

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
```

- Fd = Drag force
- Kd = Drag coefficient (dimensionless)
- A = Cross-sectional area (in square meters)
- ρ = Density of the fluid (in kilograms per cubic meter)
- v = Velocity of the object relative to the fluid (in meters per second)
- vdir = Negative direction of unit vector

Simplified for game dev:

```
Drag Force (Fd) = k * ||v||^2 * -vdir
```

k = constant

---

## Friction Force

- Friction is a contact force that resists sliding between surfaces.
- **Kinetic friction** is the friction force when an object is sliding (moving) along a surface. Direction is opposite of the object's sliding direction and is parallel to the contact surface.
- **Static friction** is the friction force that prevents an object from sliding (moving) along a surface. Direction stops the object from sliding against another surface and is parallel to the contact surface.

```
Ff = μ * N * -v
```

- μ = (mu) is the coefficient of friction
- N = Normal force
- v = Negative direction of unit vector

Simplified for game dev:

```
Ff = k * -v
```

---

## Gravitational Attraction Force

- An object is falling is just "our" experience of gravity.
- As the earth pulls an object towards it due to gravitational force, the object pulls the earth as well.
- Every object with mass exerts a gravitational force on every other object.

```
Fg = G * (m1 * m2) / d^2
```

- Fg = The gravitational force between two masses
- G = The gravitational constant G ≈ 6.674 × 10^(-11) N(m/kg)^2
- m = m1 and m2 are the masses of th two objects
- d = The distance between the centers of the two masses

---

## Spring Force

The spring force is calculated according to Hooke's law, which states that, _"The force of the spring is proportional to the displacement of the spring (extended or compressed)."_

```
F = -kx
```

- F is the restoring force exerted by the spring (in newtons, N),
- k is the spring constant (in newtons per meter, N/m), which measures the stiffness of the spring,
- x is the displacement of the spring from its equilibrium position (in meters, m), where positive or negative values indicate stretching or compression.

The negative sign shows that the spring force always acts in the direction opposite to the displacement, working to return the spring to equilibrium.
