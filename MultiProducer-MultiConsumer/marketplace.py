"""
This module represents the Marketplace.
Computer Systems Architecture Course
Assignment 1
March 2020
"""

class Marketplace:
    """
        Marketplace Class that acts like a buffer for the MPMC problem
    """
    """
    Dictionary for store producers: {producer_id : [products]} 
    """
    dictProducers = {}
    """
    Dictionary for store carts: {cart_id : [(producer_id, product)]}
    """
    dictCarts = {}
    queue_size_per_producer = 0
    producersCount = 0
    cartsCount = 0

    def __init__(self, queue_size_per_producer):
        """
        Constructor
        
        :type queue_size_per_producer: Int
        :param queue_size_per_producer: the maximum size of a queue associated with each producer
        """
        self.queue_size_per_producer = queue_size_per_producer

    def register_producer(self):
        """
        Returns an id for the producer that calls this. The id represents index of producer in marketplace
        """
        self.producersCount += 1
        self.dictProducers[self.producersCount] = []
        return self.producersCount

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace

        :type producer_id: String
        :param producer_id: producer id

        :type product: Product
        :param product: the Product that will be published in the Marketplace

        :returns True or False. If the caller receives False, it should wait and then try again.
        """

        """
        If queue of products is full, producer should wait untill consumer extract from queue
        """
        if len(self.dictProducers[producer_id]) >= self.queue_size_per_producer:
            return False
        self.dictProducers[producer_id].append(product)
        return True

    def new_cart(self):
        """
        Creates a new cart for the consumer

        :returns an int (intex of cart in marketplace) representing the cart_id
        """
        self.cartsCount += 1
        self.dictCarts[self.cartsCount] = []
        return self.cartsCount

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to add to cart

        :returns True or False. If the caller receives False, it should wait and then try again
        """
        
        """
        This iterates throw dictProducers and try to find the product. If product is find then
        remove product from list of products of producer , add product to cart and return True,
        else return False
        """
        for producer_id in self.dictProducers:
            for curr_product in self.dictProducers[producer_id]:
                if curr_product == product:
                    self.dictProducers[producer_id].remove(product)
                    self.dictCarts[cart_id].append((producer_id, product))
                    return True

        return False

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to remove from cart
        """

        """
        This iteraties throw dictCarts and try o find the product. If product is find then
        remove this product from cart and add product to list of products due to producer_id
        """
        product_index = 0
        for info_product in self.dictCarts[cart_id]:
            """
            info_product = (producer_id, product)
            """
            producer_id = info_product[0]
            product_to_be_removed = info_product[1]
            if product == product_to_be_removed:
                self.dictCarts[cart_id].remove(info_product)
                self.dictProducers[producer_id].append(product)
                return

    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.

        :type cart_id: Int
        :param cart_id: id cart
        """
        listOfProducts = map(lambda info_product: info_product[1], self.dictCarts[cart_id])
        self.dictCarts[cart_id] = []
        return listOfProducts
