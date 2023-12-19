### Camera Specific
- `camera.rotation` $\theta_c$
- `camera.zoom` $z$ (the smaller the more zoomed out it is)
- `camera.target` $\overrightarrow{t_w}$
- `camera.offset` $\overrightarrow{o_w}$
- `mouse_position` $\overrightarrow{m_s}$

for now we will ignore rotations

We have two kinds of vectors.
I will label them world vectors and screen vectors appropiately denoted by the subscripts $w$, and $s$ 

    If a vector does not have a subscript assume it is a world vector

The vector that stems from the world origin to the mouse position aka the world position of the mouse will be denoted as $\overrightarrow{m_w}$

$$
\overrightarrow{m_w} = \overrightarrow{t_w}-\frac{\overrightarrow{o_w}-\overrightarrow{m_s}}{z}
$$

So for any vector $\overrightarrow{v_s}$ to turn it into $\overrightarrow{v_w}$ you would need to do the following operations
$$
\\\overrightarrow{v_w} = \overrightarrow{t_w}-\frac{\overrightarrow{o_w}-\overrightarrow{v_s}}{z}
$$
The same goes for going the other way around
$$
\\\overrightarrow{v_s} = \overrightarrow{o_w} - z(\overrightarrow{t_w} - \overrightarrow{v_w}) 
$$

#### Zooming

This is the zooming code:
```
    // Camera zoom controls
    // We want when it zooms the place where the mouse is zooming stays the same relative to the screen
    Vector2 prescroll_target_vec = ScreenToWorldVec(game, GetMousePosition());
#if 0
    //linear zoom
    game->camera.zoom +=
        ((float)GetMouseWheelMove()*0.05f*game->camera.zoom);
#elif 1
    //exponential zoom
    game->camera.zoom *= 1.0f + GetMouseWheelMove() * 0.1f;

#endif

    Vector2 delta_pos = VECTOR2_SUB((ScreenToWorldVec(game, GetMousePosition())),prescroll_target_vec);
    game->camera.target = VECTOR2_SUB(game->camera.target, delta_pos);

    // zoom caps
    if (game->camera.zoom > 4000.0) {
        game->camera.zoom = 4000.0;
    } 
    else if (game->camera.zoom < .00025) {
        game->camera.zoom = .00025;
    }
```
##### Exponential Zoom

`GetMouseWheelMove()` returns $0$, $1$, or $-1$.
In the code we don't do linear zoom so we can ignore it and instead do an exponential zoom which depending on which direction the mouse is scrolled will go from $1.1$ of its original zoom or $0.9$ since they don't multiply to $1$ going forward and then back does not return it to its original zoom level

##### Staying in place

In order for the zoom to go towards where the mouse is we shift $\overrightarrow{t_w}$ by $\Delta\overrightarrow{m_w}$ (the difference of $\overrightarrow{m_w}$ before and after the zoom if the zoom had just been from the center) 
giving us:
$$
\overrightarrow{t'_w} = \overrightarrow{t_w}-\Delta\overrightarrow{m_w}
$$
`prescroll_target_vec` is just what the world mouse position is before we scroll
$\overrightarrow{m_w}$.
Post scroll the new world vector for the mouse doesn't need a variable so it is just `ScreenToWorldVec(game, GetMousePosition())` $\overrightarrow{m'_w}$
$$
\Delta\overrightarrow{m_w} = \overrightarrow{m'_w}-\overrightarrow{m_w}
$$


