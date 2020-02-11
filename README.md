# cli-mandelbrot-set

A cli-based mandelbrot set generator.
The adventage of rendering fractals in cli is the lower resolution, which results in quicker rendering.
When the desired coordinates are found, the view can be exported to a high-resolution image.


## Screenshots

![cli-mandelbrot-set](https://i.imgur.com/MGhuKRA.png)
_Commandline interface_

![exported-mandelbrot-set](https://i.imgur.com/B0UROKl.png)
_Exported image_

## Getting Started

To compile the executable 'app', run compile.sh
```bash
chmod +x compile.sh
./compile.sh
```

Then run the application
```bash
chmod +x app
./app
```

### Features

#### Shortcuts
 - r = reset view to initial coordinates
 - i = input settings
 - s = export photo
 - 5 = reload



## Planned features
 - infinite zoom
 - save as video (by zooming to cords)
 - support GPU-rendering
 - easier integration for color-schemas (using config perhaps)
 - better color methods/schemas
 - saving bookmarks
