extern crate libc;
use libc::{c_int, c_void};

pub struct DummyQueue {
}

pub struct DummyHandle {
}

#[no_mangle]
pub extern fn queue_init(queue_ptr: *mut DummyQueue, nprocs: c_int) {
}

#[no_mangle]
pub extern fn queue_register(queue_ptr: *mut DummyQueue, handle_ptr: *mut DummyHandle, thread_id: c_int) {
}

#[no_mangle]
pub extern fn enqueue(queue_ptr: *mut DummyQueue, handle_ptr: *mut DummyHandle, value: *mut c_void) {
}

#[no_mangle]
pub extern fn dequeue(queue_ptr: *mut DummyQueue, handle_ptr: *mut DummyHandle) -> *mut c_void {
    std::ptr::null_mut()
}

#[no_mangle]
pub extern fn queue_free(queue_ptr: *mut DummyQueue, handle_ptr: *mut DummyHandle) {
}


#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
    }
}
