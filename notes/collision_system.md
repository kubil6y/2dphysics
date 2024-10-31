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
M = m * V
```

- M is the momentum
- m is the mass of the object
- V is the velocity of the object

- **Momentum** is a measurement of mass in motion.
- Momentum can be thought of a body's **tendency** to stay in motion.
- You might have heard of the term **conservation of momentum**. This means that total moment of a system should always be constant.
- As objects _collide_, they impart some of their momentum on the other object, reducing their own. (ex: pool white ball hitting, red ball)

```
m1V1 + m2V2 = m1V1' + m2V2'
```
