# Double-Check locking pattern

Useful on multithreading applications to prevent unneeded acquires to mutex

```cpp
mutex.lock();
if(condition){
    // Secure block 
}
mutex.unlock();
```

If condition is due to always be false and this code is called multiple times by different threads, it is better to
apply DCLP:

```cpp
if(condition){
    mutex.lock();
    if(condition){
        // Secure block 
    }
    mutex.unlock();
}
```

This way, we will avoid locking the mutex.

## Problems with DCLP

Runtime conditions can be caused if this pattern is not used carefully

For example a singleton instantiation:
```cpp
if(!instance){
    mutex.lock();
    if(!instance){
        instance = new Instance();
    }
    mutex.unlock();
}
```
Read and write of `instance` on first if is thread unsafe!

`new` in C++ is done in 3 thread unsafe steps:

1. Memory allocation
2. Initialization
3. Memory address assignment

```cpp
m_instance = new Instance{};
```

Will be decomposed in:
```cpp
void *p = operator new (sizeof(Instance));  // 1. Memory allocation
new(p) Instance{};                          // 2. Initialization
m_instance = static_cast<Instance*>(p);     // 3. Memory address assignment
```
If this instructions were guaranteed to be executed in order, DCLP on new operators will always be thread safe,
but optimization may occur:


```cpp
void *p = operator new (sizeof(Instance));  // 1. Memory allocation
m_instance = static_cast<Instance*>(p);     // 3. Memory address assignment
new(p) Instance{};                          // 2. Initialization
```

If a thread gets preemptive between step 3 and 2, another thread could check
the first `if(!instance)`, returning false because `m_instance` is no longer
`nullptr`, and that thread will continue executing with a dangling pointer!

