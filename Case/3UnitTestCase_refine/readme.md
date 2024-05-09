# basic 3 Unit Mesh

[OpenFOAM中三单元测试案例之网格数据 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/409130279)

# Refine The basic Mesh

It's very easy to refine the rectangular mesh. Just use the `refineMesh` command.

```bash
refineMesh
```

openfoam will create a 0.05 folder in the case folder, run paraview to check the mesh.

```bash
touch .foam
paraview.exe .foam
```

or you can just change /system/blockMeshDict/blocks like this:
```
    hex (0 1 2 3 4 5 6 7) (3 9 9) simpleGrading (1 1 1)
```

Then run `blockMesh` again.

```bash
blockMesh
```
