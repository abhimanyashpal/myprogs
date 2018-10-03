import logging

def my_logger(func):
    """ A closure basically packages the inner function with
    all the local variables that are in the scope of the outer
    function and these continue to persist even after the outer 
    function completes execution
    """

    #This function will not be executed yet.
    def inner_func(*args):
        logging.warning('Going to execute {} with {}'.format(func.__name__,args))
        print func(*args)

    #We return it just like a pointer
    return inner_func


def add(x, y):
    return x+y

def sub(x,y):
    return x-y


#Now we have 2 entities which one can think as 
# function pointers but is much more since when
# we call it , it also remembers all the local 
# variables when it was created

add_logger = my_logger(add)
sub_logger = my_logger(sub)


add_logger(2,3)
sub_logger(10,4)
