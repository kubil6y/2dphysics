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

### Projection Method

Perhaps the simplest and most intuitive method of resolving interpenetrations would be simply separate them out by changing their **positions** in opposite direction along the collision **normal**. This is known as **projection method**.

```
da = depth * mb / (ma + mb)
db = depth * ma / (ma + mb)

By using inverse mass:

da = depth / (1/ma + 1/mb) * 1/ma
db = depth / (1/ma + 1/mb) * 1/mb
```
