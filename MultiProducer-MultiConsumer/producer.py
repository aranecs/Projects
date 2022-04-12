"""
This module represents the Producer.
Computer Systems Architecture Course
Assignment 1
March 2020
"""

from threading import Thread
from time import sleep

class Producer(Thread):
    """
    Class that represents a producer.
    """
    products = []
    marketplace = None
    republish_wait_time = 0.0
    producer_id = 0

    def __init__(self, products, marketplace, republish_wait_time, **kwargs):
        """
        Constructor.
        
        @type products: List()
        @param products: a list of products that the producer will produce
        
        @type marketplace: Marketplace
        @param marketplace: a reference to the marketplace
        
        @type republish_wait_time: Time
        @param republish_wait_time: the number of seconds that a producer must
        wait until the marketplace becomes available
        
        @type kwargs:
        @param kwargs: other arguments that are passed to the Thread's __init__()
        
        The constructor starts the Thread and registers the Thread as a producer
        """
        Thread.__init__(self, **kwargs)
        self.products = products
        self.marketplace = marketplace
        self.producer_id = marketplace.register_producer()
        self.republish_wait_time = republish_wait_time


    def run(self):
        """
        index : index of product in list products
        """
        index = 0
        """
        productsCount : count of products in list of products
        """
        productsCount = len(self.products)
        """
        The thread function iterates infinitely through the provided list. For each product
        tries to publish it until all products of that type where published, sleeping accordingly
        """
        while True:
            """
            products[index] = ["productName", productQuantity, productTimeToProduce]
            """
            product = self.products[index]
            productName = product[0]
            productQuantity = product[1]
            productTimeToProduce = product[2]
            while productQuantity > 0:
                sleep(productTimeToProduce)
                while self.marketplace.publish(self.producer_id, productName) is False:
                    sleep(self.republish_wait_time)
                productQuantity -= 1
            index += 1
            """
            If list was fully iterated => start again from index = 0
            """
            if index == productsCount:
                index = 0
