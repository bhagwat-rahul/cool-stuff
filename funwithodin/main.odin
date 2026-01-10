package main
import "core:fmt"
import "core:thread"

colors := [?]string{"White", "Red", "Green", "Blue", "Octarine", "Black"}

main :: proc() {
	parallel_process()
}

parallel_work :: proc(t: ^thread.Thread) {
	for color in colors {
		fmt.println(color)
	}
}

parallel_process :: proc() {
	thread_array := make([dynamic]^thread.Thread, 0, len(colors))

	for _ in colors { 	// creates and starts 6 threads
		if t := thread.create(parallel_work); t != nil {
			t.init_context = context
			t.user_index = len(thread_array)
			append(&thread_array, t)
			thread.start(t)
		}
	}

	for len(thread_array) > 0 {
		for i := 0; i < len(thread_array); {
			if t := thread_array[i]; thread.is_done(t) {
				thread.destroy(t)
				ordered_remove(&thread_array, i)
			} else {
				i += 1
			}
		}
	}
}
