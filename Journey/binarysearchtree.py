class BinarySearchNode:
    def __init__(self,data):
        self.data = data
        self.left = None
        self.right = None

    def add_child(self,data):
        if data == self.data:
            return
        if data < self.data:
            #add data in left subtree
            if self.left:
                self.left.add_child(data)
            else:
                self.left = BinarySearchNode(data)
                
        else:
            if self.right:
                self.right.add_child(data)
            else:
                self.right = BinarySearchNode(data)

    def inorder_traversal(self):
        elements = []
        #visit left tree
        if self.left:
            elements += self.left.inorder_traversal()
        #visit base node
        elements.append(self.data)
        #vist right tree
        if self.right:
            elements += self.right.inorder_traversal()
        return elements

    def preorder_traversal(self):
        elements = []
        #visit base node
        elements.append(self.data)
        if self.left:
            elements += self.left.preorder_traversal()
        if self.right:
            elements += self.right.preorder_traversal()
        return elements
    
    def postorder_traversal(self):
        elements = []
        if self.left:
            elements += self.left.postorder_traversal()
        if self.right:
            elements += self.right.postorder_traversal()
        elements.append(self.data)
        return elements
    

    def search(self,val):
        if self.data == val:
            return True
        if val < self.data:
            if self.left:
                return self.left.search(val)
            else:
                return False
        if val > self.data:
            if self.right:
                return self.right.search(val)
            else:
                return False
    def find_min(self):
        mini = self.data
        if self.left:
            mini= self.left.find_min()
        return mini

    def find_max(self):
        maxi = self.data
        if self.right:
            maxi = self.right.find_max()
        return maxi
    def summation(self):
        left_sum = self.left.summation() if self.left else 0
        print(left_sum)
        right_sum = self.right.summation() if self.right else 0
        print(right_sum)
        return self.data + left_sum + right_sum

    def delete(self,val):
        if val < self.data:
            if self.left:
                self.left.delete(val)
        elif val > self.data:
            if self.right:
                self.right.delete(val)
        else:
            if self.left is None and self.right is None:
                return None
            if self.left is None
            
            

def build_tree(elements):
    root = BinarySearchNode(elements[0])

    for i in range(1,len(elements)):
        root.add_child(elements[i])

    return root

if __name__ == '__main__':
    numbers = [17,4,1,20,9,23,18,34]
    numbers_tree = build_tree(numbers)
    print(numbers_tree.postorder_traversal()
          )

    
