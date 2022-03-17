
class HashTable:
    def __init__(self):
        self.MAX = 10
        self.arr = [[] for i in range(self.MAX)] #an array filled with nones
        

    def get_hash(self,key):
        hash = 0
        for char in key:
            hash += ord(char) #each character is converted to unicode equivalent
        return hash % self.MAX

    def __setitem__(self,key,value):
        hash = self.get_hash(key)
        found = False
        #self.arr[hash]= value#adds the value of the key to the array[hash]
        for idx, element in enumerate(self.arr[hash]): #iterate over the loop
            if len(element) == 2 and element[0] == key: 
                self.arr[hash][idx] = (key,value)
                found = True
                break
             
        if not found:
            self.arr[hash].append((key,value))
               

    def __getitem__(self,key):
        hash = self.get_hash(key)
        for element in self.arr(hash):
            if element[0] == key:
                return element[1]

    def __delitem__(self,key):
        hash = self.get_hash(key)
        for index, element in enumerate(self.arr[hash]):
            if element[0]==key:
                del self.arr[hash][index]

#creating an object
t = HashTable()

    
    
