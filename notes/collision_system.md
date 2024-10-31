# Collision System

Regardless of the shape, our collision contact information will always contain:

- Start point
- End point
- A normal direction
- The depth of the collision

## Collision Detection

1. Collision Detection (shape specific)
2. Is Colliding?
3. Compute Collision Information
4. Collision Resolution (shape agnostic)

## Collision Response

We can choose different methods to **resolve** collisions:

- Projection method
  - Adjust the positon of the colliding objects
- Impulse method
  - Adjust the **velocity** of the colliding objects by applying impulses
- Penalty method
  - Adjust the **acceleration** of colliding objects

These collision response methods are typically applied **separately**, based on the specific requirements of the simulation or game engine. Here’s a bit more on how each might be chosen or combined:

1. **Projection method**: Often used to correct positions after a collision is detected. It simply moves objects apart to prevent overlapping. This can be used alone, or in combination with other methods if only positional adjustment is needed without changes to velocity.

2. **Impulse method**: Adjusts the velocity of objects on collision by calculating and applying an impulse, typically providing a realistic response like bouncing. It’s often used in physics simulations where conservation of momentum is important. This method is usually applied separately but can be combined with the projection method for better accuracy (position correction + velocity change).

3. **Penalty method**: Adds a small force over time, effectively increasing acceleration to separate overlapping objects. It’s less accurate than impulses but computationally simpler, commonly used in soft-body physics where elasticity is desired. This is usually applied on its own or with minor projection adjustments.

Using **multiple methods simultaneously** is possible but less common since each has a distinct approach to collision resolution.

### 1. Projection Method

Perhaps the simplest and most intuitive method of resolving interpenetrations would be simply separate them out by changing their **positions** in opposite direction along the collision **normal**. This is known as **projection method**.

```
da = depth * mb / (ma + mb)
db = depth * ma / (ma + mb)

By using inverse mass:

da = depth / (1/ma + 1/mb) * 1/ma
db = depth / (1/ma + 1/mb) * 1/mb
```

### 2. The Impulse Method

- The impulse method allows us to directly change the **velocities** of the bodies that just collided.
- Here the velocity changes are instant. They take new values, and the duration of the frame does not affect the result.
- This is achieved through the application of an **impulse** to both objects, which can be thought as an immediate transfer of **momentum** between the objects in a system.

#### Momentum

```
P = m * V
```

- P is the momentum
- m is the mass of the object
- V is the velocity of the object

- **Momentum** is a measurement of mass in motion.
- Momentum can be thought of a body's **tendency** to stay in motion.
- You might have heard of the term **conservation of momentum**. This means that total moment of a system should always be constant.
- As objects _collide_, they impart some of their momentum on the other object, reducing their own. (ex: pool white ball hitting, red ball)

```
m1V1 + m2V2 = m1V1' + m2V2'
```

- **Impulse** is a change in momentum by performing a direct change in **velocity**.

Impulse:

```
J = FΔt = mΔv
Δv = J / m
```
