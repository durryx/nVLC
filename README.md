# nVLC
nVLC is a ncurses based video player from the terminal. It currently support terminal scaling and operates with fixed 18 FPS. <br>
Compile with `gcc main.c -o nvlc -lpthread`
## Images
[comment]: <> (TODO video selection & performance issue)
![image](nVLC_2.png)
![image](nVLC_1.png)

# The idea

```mermaid
stateDiagram-v2
    [*] --> nvlc

    state nvlc {
				 data: ffprobe (get video info)
				 ffmpeg: ffmpeg (extract frames)
				 time: increment video time
       	[*] --> data
				[*] --> ffmpeg
        ffmpeg --> time : pass parameters
        time --> ffmpeg : cache
        --
				init: init /cache
				join: dealloc & join
				state B {
      	direction LR
				del: rm IMG*
				next: next IMG*++
      	jp2a --> del : print IMG* to stdout
				del --> next
				next --> jp2a
    		}

        [*] --> init
				init --> bar.sh : wait for other process to init
				bar.sh --> B
				B --> join
				join --> [*]
    }
```
