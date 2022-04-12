"""
This module represents the Consumer.
Computer Systems Architecture Course
Assignment 1
March 2020
"""

from threading import Thread, current_thread
from time import sleep

class Consumer(Thread):
    """
    Class that represents a consumer.
    """
    carts = []
    marketplace = None
    retry_wait_time = 0.0
    cart_id = 0

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.
        
        :type carts: List
        :param carts: a list of add and remove operations
        
        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace
        
        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available
        
        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self, **kwargs)
        self.carts = carts
        self.marketplace = marketplace
        self.retry_wait_time = retry_wait_time
        self.cart_id = self.marketplace.new_cart()

    def run(self):
        """
        Carts represents a list of lists of dictionaries, so I need to iterate throw it.
        """
        for listOfOperations in self.carts:
            for operation in listOfOperations:
                operationType = operation['type']
                product = operation['product']
                quantity = operation['quantity']
                """
                If operationType is add => add_to_cart the product if product is available
                """
                if operationType == "add":
                    while quantity > 0:
                        if self.marketplace.add_to_cart(self.cart_id, product) is True:
                            quantity -= 1
                        else:
                            sleep(self.retry_wait_time)
                else:
                    """
                    else remove product from cart
                    """
                    while quantity > 0:
                        self.marketplace.remove_from_cart(self.cart_id, product)
                        quantity -= 1
        """
        After add/remove operations => place order 
        """
        for productName in self.marketplace.place_order(self.cart_id):
            print(current_thread().getName(), "bought", productName, sep=' ', flush=True)
