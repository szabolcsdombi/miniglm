# Benchmark

[benchmark.py](benchmark.py)

```
Running add_mul (<class 'glm.Vec3'>, (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), 0.0, 10000000) - 4.291233649017756 seconds
Running add_mul (<class '__main__.PyVec3'>, (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), 0.0, 10000000) - 50.73886674519271 seconds
Running add_mul (<built-in function array>, (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), 0.0, 10000000) - 37.057630215265895 seconds
----------------------------------------
Running add_add_add (<class 'glm.Vec3'>, (0.0, 0.0, 0.0), 1000000) - 3.8114269981292352 seconds
Running add_add_add (<class '__main__.PyVec3'>, (0.0, 0.0, 0.0), 1000000) - 99.79662678370208 seconds
Running add_add_add (<built-in function array>, (0.0, 0.0, 0.0), 1000000) - 46.923799226165954 seconds
```

_wip_
