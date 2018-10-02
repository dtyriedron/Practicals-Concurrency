#include <mutex>
#include <memory>
#include <stack>
#include <execution>

template<typename T>
class threadsafe_stack{
private:
    //the actual stack object that we are using
    std::stack<T> data;
    //the mutex to control access
    mutable std::mutex mut;
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack &other) {
        //we need to copy from other the other stack. Lock other stack
        std::lock_guard<std::mutex> lock(other.mut);
        data = other.data;
    }

    void push(T value){
        //lock access to the object
        std::lock_guard<std::mutex> lock(mut);
        //push the value onto the internal stack
        data.push(value);
    }

    T pop(){
        //lock access to the object
        std::lock_guard<std::mutex> lock(mut);
        //check if the stack is emtpy
        if (data.empty()) throw std::exception();
        //acesss value at the top of the stack
        auto res = data.top();
        //remove the top item form the stack
        data.pop();
        //return res
        return res;
    }

    bool empty() const{
        std::lock_guard<std::mutex> lock(mut);
        return data.empty();
    }
    void pusher(std::shared_ptr<threadsafe_stack<unsigned  int>> stack){
        //pusher will push 1 million values onto the stack
        for (unsigned int i =0; i < 1000000; ++i){
            stack->push(i);
            //make the pusher yield. will give priority to another thread
            std::this_thread::yield();
        }
    }

    void popper(std::shared_ptr<threadsafe_stack<unsigned int>> stack){
        //popper will pop 1 million values from the stack
        //we do this using a counter and a while loop
        unsigned int count = 0;
        while (count < 1000000){
            //try and pop a value
            try {
                auto val = stack->pop();
                //item popped. increment count
                ++count;
            }
            catch(std::exception e){
                //item not popped
                std::cout << e.what() << std::endl;
            }
        }
    }
};;