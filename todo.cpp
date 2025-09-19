#include <iostream>
#include <string>
#include <vector>

struct Node{
    std::string task;
    int key;
    Node(std::string newTask, int newKey){
        key = newKey;
        task = newTask;
    }
};
class maxHeap{
    public:
    std::vector<Node> taskList; 
    maxHeap(){ // this constructor essentially acts as our "buildmaxHeap" function since we're creating the list as we go
    }
    void maxHeapify(std::vector<Node>& list, int i, int size){
        int largestNode = i;
        int left = getLeft(i);
        int right = getRight(i);
        if(left < size && list[left].key > list[largestNode].key){
            largestNode = left;
        }
        if(right < size && list[right].key > list[largestNode].key){
            largestNode = right;
        }
        if(largestNode != i){
            std::swap(list[i], list[largestNode]);
            maxHeapify(list, largestNode, size);
        }
    }
    void maxHeapifyUp(std::vector<Node>& list, int i){
        while(i > 0){ // maxheapifyUp until we reach the root (index 0)
        int parentIndex = getParent(i);
            if(list[i].key > list[parentIndex].key){
                std::swap(list[i], list[parentIndex]);
                i = parentIndex;
            }else{
                break;
            }
        }
    }
    void insertion(Node newTask){
        taskList.push_back(newTask);
        maxHeapifyUp(taskList, taskList.size()-1);
    }
    void deletion(int taskNum){ 
        Node selectedNode = findTask(taskNum);
        int taskIndex = grabIndex(selectedNode);
        std::swap(taskList[taskIndex], taskList[taskList.size()-1]); // swaps the task we want to delete with the last element in vector
        taskList.pop_back(); // deletes the task we've now put at the end of the vector
        maxHeapify(taskList, 0, taskList.size()); // reheaps from the current index
    }
    void changePriority(int taskNum, int newPriority){
        int originalPriority;
        Node selectedNode = findTask(taskNum);
        int taskIndex = grabIndex(selectedNode);

        originalPriority = selectedNode.key;
        taskList[taskIndex].key = newPriority;
        if(newPriority < originalPriority){
            maxHeapify(taskList, taskIndex, taskList.size());
        }
        if(newPriority > originalPriority){
            maxHeapifyUp(taskList, taskIndex);
        }
    }
    Node findTask(int taskNum){ // grabs the task at the given number in the ordered list provided by outputList()
        std::vector<Node> copiedTaskList = taskList;
        int taskNumber = 1;
        int copiedSize = taskList.size();
        while(taskNumber != taskNum){
           std::swap(copiedTaskList[0], copiedTaskList[copiedSize-1]);
           taskNumber++;
           copiedSize--;
           maxHeapify(copiedTaskList, 0, copiedSize);
        }
        return copiedTaskList[0];
    }
    void outputList(){
        std::vector<Node> copiedTaskList = taskList;
        int taskNumber = 1;
        int copiedSize = taskList.size();
        while(copiedSize > 0){
           std::cout << taskNumber << ". > " << copiedTaskList[0].task << " | Priority: " << copiedTaskList[0].key << std::endl;
           std::swap(copiedTaskList[0], copiedTaskList[copiedSize-1]);
           taskNumber++;
           copiedSize--;
           maxHeapify(copiedTaskList, 0, copiedSize);
        }
    }
    int getParent(int i){
        i = (i-1)/2;
        return i;
    }
    int getLeft(int i){
        i = (2*i)+1;
        return i;
    }
    int getRight(int i){
        i = (2*i)+2;
        return i;
    }
    int grabIndex(Node node){
        for(int i = 0; i < taskList.size(); i++){
            if(taskList[i].task == node.task){
                return i;
            }
        }
        return 1;
    }
    bool isEmpty(){
        if(taskList.size() == 0){
            return true;
        }
        return false;
    }
};
int main(){
    bool programEnd = false;
    maxHeap priorityQ;
    while(programEnd != true){
        int choice;
        if(priorityQ.isEmpty() == true){
            std::cout << "No tasks!" << std::endl;
        }else{
            priorityQ.outputList();
        }
        std::cout << "----------------------------" << std::endl;
        std::cout << "> 1. Add a task" << std::endl;
        std::cout << "> 2. Change task priority" << std::endl;
        std::cout << "> 3. Complete a task" << std::endl;
        std::cout << "> 4. End program" << std::endl;
        std::cout << "----------------------------" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 1: {
                int key;
                std::string task;
                std::cout << "What task would you like to add?" << std::endl;
                std::cin.ignore();
                std::getline(std::cin, task);
                std::cout << "What priority should it be? (on a scale from 1-100)" << std::endl;
                std:: cin >> key;
                Node newTask(task, key);
                priorityQ.insertion(newTask);
                break;
            }
            case 2: {
                if(priorityQ.taskList.size() == 0){
                    std::cout << "You have no tasks at this time" << std::endl;
                    break;
                }
                int changeChoice;
                std::cout << "What task would you like to change? (tasks are indexed by 1)" << std::endl;
                std::cin >> changeChoice;
                if(changeChoice > priorityQ.taskList.size() || changeChoice < 1){
                    std::cout << "Not a valid choice" << std::endl;
                    break;
                } else{
                    int newPriority;
                    std::cout << "Great! Now what would you like to change the priority to?" << std::endl;
                    std::cin >> newPriority;
                    priorityQ.changePriority(changeChoice, newPriority);
                    break;
                }
            }
            case 3: {
                int completeChoice;
                std::cout << "What task would you like to complete? (tasks are indexed by 1)" << std::endl;
                std::cin >> completeChoice;
                if(completeChoice > priorityQ.taskList.size() || completeChoice < 1){
                    std::cout << "Not a valid choice" << std::endl;
                    break;
                } else{
                    priorityQ.deletion(completeChoice);
                    std::cout << "Task completed! Good work!" << std::endl;
                    break;
                }
            }
            case 4:
                programEnd = true;
                break;
        } 
    }
    return 0;
}