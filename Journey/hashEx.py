#Read the csv file into the hash table
#Find the avg of first 7days
#Maximum of all the days

"""
weather = []
with open("nyc_weather.csv","r") as file:
    for line in file:
        token = line.split(',')
        try:
            temp = int(token[1])
            weather.append(temp)
        except:
            print("Invalid temperature. Ignore the row")
            
 """ 
"""
weather= {}

with open("nyc_weather.csv","r") as file:
    for line in file:
        token = line.split(',')
        day = token[0]
        try:
            temp = int(token[1])
            weather[day] = temp
        except:
            print("Invalid temperature. Ignore the row")
"""
"""
poem = {}
with open("poem.txt","r") as file:
    for line in file:
        words = line.split(' ')
        for word in words:
            word = word.replace('\n','')
            if word in poem:
                poem[word]+=1
            else:
                poem[word]=1
                
"""

class HashTable:
    def __init__(self):
        self.MAX = 10
        self.arr = [None for i in range(self.MAX)] #an array filled with []
        

    def get_hash(self,key):
        hash = 0
        for char in key:
            hash += ord(char) #each character is converted to unicode equivalent
        return hash % self.MAX

    def __setitem__(self,key,value):
        hash = self.get_hash(key)
        if self.arr[h] is None:
            self.arr[h] = (key,val)
        else:
            new_hash = self.find_slot(key,hash)
            self.arr[new_hash] = (key,val)
        print(self.arr)
       
               

    def __getitem__(self,key):
        hash = self.get_hash(key)
        if self.arr[hash] is None:
            return
        prob_range = self.get_prob_range(hash)
        for prob_index in prob_range:
            element = self.arr[prob_index]
            if element  is None:
                return
            if element[0] == key:
                return element[1]
            








    def get_prob_range(self,index):
        return [*range(index,len(self.arr))]+ [*range(0,index)]

    def find_slot(self,key,index):
        prob_range = self.get_prob_range(index)
        for prob_index in prob_range:
            if self.arr[prob_index] is None:
                return prob_index
            if self.arr[prob_index][0] == key:
                return prob_index
        raise Exception("Hashmap full")



    def __delitem__(self,key):
        hash = self.get_hash(key)
        prob_range = self.get_prob_range(hash)
        for prob_index in prob_range:
            if self.arr[prob_index] is None:
                return
            if self.arr[prob_index][0] ==key:
                self.arr[prob_index] = None
        print(self.arr)
        

#creating an object
t = HashTable()
