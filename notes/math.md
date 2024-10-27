# Math Notes

- The derivative of position is velocity
- The derivative of velocity is acceleration

## Integration Techniques

1. Explicit Euler:

Uses the current velocity to estimate the new position and current acceleration to estimate the new velocity.

2. Implicit Euler:

One of the simplest and aarguably the most popular integration technique for **game** physics. Its accuracy is "good enough" for most game applications. The drawback is that it requires solving a system of equations per time-step.

3. Verlet Integration:

Provides greater accuracy than Implicit Euler and less memory usage when simulating a **large number of particles**.

4. Runge-Kutta Integration:

This Runge-Kutta is a family of integrations, named after German physicists Carl Runge and Martin Kutta. The RK4 is the most popular implementation. It accumulates error is on the order of the **fourth** derivative. This makes RK4 very accurate. Much more accurate than Euler, which is only first order.

| Method         | Stability        | Accuracy | Computational Cost |
| -------------- | ---------------- | -------- | ------------------ |
| Explicit Euler | Low              | Low      | Very Low           |
| Implicit Euler | High             | Moderate | Moderate           |
| Verlet         | Moderate to High | Moderate | Low to Moderate    |
| RK4            | High             | High     | High               |
