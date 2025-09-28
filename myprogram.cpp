#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstdlib>
using namespace std;
//МАССИВ
struct Numbers //Сам массив (его составляющие)
{
    int* num;
    int size;
    int C;
};
void createMas(Numbers& A, int C) { //Создать массив
    A.num = new int[C];
    A.size = 0; // изначально элементов нет
    A.C = C;
}
void addMasAtInd(Numbers& A, int ind, int znach) { //Добавить элемент по индексу
    if (ind >= A.C) {
        cout << "Индекс вне диапазона емкости массива.\n";
        return;
    }
    if (ind >= A.size) {
        A.size = ind + 1;
    }
    A.num[ind] = znach;
}
void addMasAtEnd(Numbers& A, int znach) { //Добавить в конец
    if (A.size >= A.C) {
        cout << "Массив заполнен." << endl;
        return;
    }
    A.num[A.size] = znach;
    A.size++;
}
void poiskMasPoInd(Numbers& A, int ind) { //Получение по индексу
    if (ind <0 || ind > A.size) {
        cout << "Выход за границы массива." << endl;
        return;
    }
    else cout << A.num[ind] << endl;
}
void deleteMasPoInd(Numbers& A, int ind) { //Удалить по индексу
    if (ind <=0 || ind > A.size) {
        cout << "Элемента за границами массива быть не может." << endl;
        return;
    }
    else {
        for (int i = ind; i < A.size; i++)
        {
            A.num[i - 1] = A.num[i];
        }
        A.size--;
    }
}
void ZamenaMas(Numbers& A, int ind, int znach){ //Заменить по индексу
    if (ind <= 0 || ind > A.size) {
        cout << "Нельзя заменить то что не существует." << endl;
        return;
    }
    else {
        A.num[ind] = znach;
    }
}
void RazmerMas(Numbers& A){ //Размер массива
    cout << A.size << endl;
}
void readMas(Numbers& A){ //Чтение
    if (A.size == 0){
        cout << "Массив пустой, Ваша честь.";
        return;
    }
    for (int i = 0; i < A.size; i++)
    {
        cout << A.num[i] << " ";
    }
    cout << endl;
}
//ОДНОСВЯЗНЫЙ СПИСОК
struct Spisok //Сам односвязный список (его составляющие)
{
    string name;
    Spisok* place;
};
void CreateList(Spisok*& List, string str) //Создание
{
    List = new Spisok{ "Лунтик", nullptr };
}
void AddChelPosle(Spisok* ptr, string str) //Добавить человека в односвязный список после ptr
{
    Spisok* element = new Spisok;
    element->name = str;
    element->place =ptr->place;
    ptr->place = element;
}
void AddChelDo(Spisok*& head, Spisok* ptr, string str) {//Добавить человека в односвязный список до ptr
    Spisok* element = new Spisok;
    element->name = str;
    if (head == ptr){
        element->place = head;
        head = element;
    }
    else {
        Spisok* per = head;
        while (per && per->place != ptr) {
            per = per->place;
        }
        if (per) {
            element->place = ptr;
            per->place = element;
        }
        else {
            delete element;
        }
    }
}
void AddToEnd(Spisok*& ptr, string n) //Добавить в конец односвязного списка
{
    Spisok* element = new Spisok;
    element->name = n;
    element->place = nullptr;
    Spisok* temp = ptr;
    while (temp->place != nullptr){
        temp = temp->place;
    }
    temp->place = element;
}
void AddToBegin(Spisok*& ptr, string n) //Добавить в начало односвязного списка
{
    Spisok* element = new Spisok;
    element->name = n;
    element->place = ptr;
    ptr = element;
}
void print(Spisok* ptr) //Печать односвязного списка - печатаем элемент и сдвигаемся на следующий указатель, пока не наткнемся на nullptr
{
    while (ptr != nullptr){
        cout << ptr->name << " ";
        ptr = ptr->place;
    }
    cout << endl;
}
void otherPrint(Spisok* ptr) { //Другая печать односвязного списка - с помощью рекурсии 
    if (ptr == nullptr) {
        return; 
    }
    otherPrint(ptr->place); //с конца
    cout << ptr->name << " ";
    //otherPrint(ptr->place); //с начала
}
int SizeList(Spisok* ptr) //Размер односвязного списка - сменяем указатели, пока не наткнемся на nullptr
{
    int count = 0;
    while (ptr != nullptr){
        count++;
        ptr = ptr->place;
    }
    return count;
}
bool poisk(Spisok* ptr, string str){ //Поиск элемента по значению (есть или нет)
    Spisok* element = ptr;
    while (element != nullptr) {
        if (element->name == str) return true;
        element = element->place;
    }
    return false;
}
void deletePoZnach(Spisok*& ptr, string str){ //Удаление по значению
    if (ptr == nullptr) return;
    if(!poisk(ptr, str)) cout << "Нельзя удалить несуществующий элемент" << endl;
    else {
        Spisok* element = ptr;
        Spisok* prev = nullptr;
        while (element != nullptr && element->name != str) {
            prev = element;
            element = element->place;
        }
        if (prev == nullptr) {
            ptr = element->place;
        }
        else {
            prev->place = element->place;
        }
        delete element;
    }
}
void deleteToBegin(Spisok*& ptr) //Удалить начало односвязного списка
{
    if (ptr == nullptr) return;
    if (ptr->place == nullptr) {
        delete ptr;
        ptr = nullptr;
        return;
    }
    Spisok* element = ptr;
    ptr = ptr->place;
    delete element;
}
void deleteToEnd(Spisok*& ptr) //Удалить конец односвязного списка
{
    if (ptr == nullptr) return;
    if (ptr->place == nullptr) {
        delete ptr;
        ptr = nullptr;
        return;
    }
    Spisok* temp = ptr;
    while (temp->place->place != nullptr) {
        temp = temp->place;
    }
    delete temp->place;
    temp->place = nullptr;
}
Spisok* FindElement(Spisok* ptr, string str) { //Поиск элемента (вернуть указатель)
    Spisok* element = ptr;
    while (element != nullptr) {
        if (element->name == str) return element;
        element = element->place;
    }
    return nullptr;
}
void deleteChelDo(Spisok*& ptr, Spisok* target) { //Удалить до заданного значения
    if (ptr == nullptr || target == nullptr) return;
    if (ptr == target) return;
    Spisok* prevPrev = nullptr;
    Spisok* prev = ptr;    
    Spisok* element = ptr->place; 
    while (element != nullptr && element != target) {
        prevPrev = prev;
        prev = element;
        element = element->place;
    }
    if (element != target) {
        return;
    }
    if (prevPrev == nullptr) {
        deleteToBegin(ptr);
        ptr = element; 
    }
    else {
        prevPrev->place = prev->place;
        delete prev;
    }
}
void deleteChelPosle(Spisok* ptr) {// Удаляет после заданного значения
    if (ptr == nullptr || ptr->place == nullptr) return;
    Spisok* element = ptr->place;
    ptr->place = element->place;
    delete element;
}

//ДВУСВЯЗНЫЙ СПИСОК
struct Group {
    string student;  // студент 
    Group* next;  // указатель на следующий элемент  
    Group* last;  // указатель на предыдущий элемент  
};
void AddStudPosle(Group* ptr, string n) {
    Group* element = new Group;
    element->student = n;
    element->next = ptr->next;
    element->last = ptr;
    if (ptr->next != nullptr) {
        ptr->next->last = element;
    }
    ptr->next = element;
}
void AddStudDo(Group* ptr, string n) {
    if (ptr == nullptr) return; 
    Group* element = new Group;
    element->student = n;
    element->next = ptr;
    element->last = ptr->last;
    if (ptr->last != nullptr) {
        ptr->last->next = element;
    }
    ptr->last = element;
}
void deleteStudPosle(Group* ptr, string n) {
    if (ptr == nullptr || ptr->next == nullptr) return; 
    Group* element = ptr->next;
    if (element->next != nullptr) {
        element->next->last = ptr;
    }
    ptr->next = element->next;
    delete element;
}
void deleteStudDo(Group* ptr, string n) {
    if (ptr == nullptr || ptr->last == nullptr) return; 
    Group* element = ptr->last;
    if (element->last != nullptr) {
        element->last->next = ptr;
    }
    ptr->last = element->last;
    delete element;
}
void AddToStart(Group*& head, string n) {
    Group* newNode = new Group;
    newNode->student = n;
    newNode->next = head;
    newNode->last = nullptr;
    if (head != nullptr) {
        head->last = newNode;
    }
    head = newNode;
}

// Добавление в конец списка
void AddToEnd(Group*& head, string n) {
    Group* newNode = new Group;
    newNode->student = n;
    newNode->next = nullptr;
    if (head == nullptr) {
        newNode->last = nullptr;
        head = newNode;
        return;
    }
    Group* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->last = temp;
}

// Удаление из начала списка
void DeleteFromStart(Group*& head) {
    if (head == nullptr) return;
    Group* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->last = nullptr;
    }
    delete temp;
}

// Удаление из конца списка
void DeleteFromEnd(Group*& head) {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Group* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    // temp — последний элемент
    temp->last->next = nullptr;
    delete temp;
}
void printGroup(Group* ptr) {
    while (ptr != nullptr) {
        cout << ptr->student << " ";
        ptr = ptr->next;
    }
    cout << endl;
}
void otherPrintGroup(Group* ptr) { //Другая печать односвязного списка - с помощью рекурсии 
    if (ptr == nullptr) {
        return;
    }
    otherPrintGroup(ptr->last); //с конца
    cout << ptr->student << " ";
    //otherPrint(ptr->next); //с начала
}
bool poiskGroup(Group* ptr, string str) { //Поиск элемента по значению (есть или нет)
    Group* element = ptr;
    while (element != nullptr) {
        if (element->student == str) return true;
        element = element->next;
    }
    return false;
}
//СТЕК
struct Garden {
    string item;  // еда 
    Garden* point;  // указатель на следующий элемент   
};
void addStack(Garden*& ptr, const string& str) {
    Garden* element = new Garden;
    element->item = str;
    element->point = ptr; 
    ptr = element;        
}
void deleteStack(Garden*& ptr) {
    if (ptr != nullptr) {
        Garden* temp = ptr;
        ptr = ptr->point; 
        delete temp;     
    }
}
void readStack(Garden* ptr) {
    if (ptr == nullptr) {
        return;
    }
    cout << ptr->item << " ";
    readStack(ptr->point);
}

//ОЧЕРЕДЬ
struct Toys {
    string toy;  // еда 
    Toys* site;  // указатель на следующий элемент   
};
void addQueue(Toys*& ptr, string str) //Функция добавления в очередь
{
    Toys* element = new Toys;
    element->toy = str;
    element->site = ptr;
    ptr = element;
}
void deleteQueue(Toys*& ptr) //Функция удаления из очереди - удаляет самый верхний - последний вставленный
{
    if (ptr == nullptr) return;
    if (ptr->site == nullptr) {
        delete ptr;
        ptr = nullptr;
        return;
    }
    Toys* temp = ptr;
    while (temp->site->site != nullptr) {
        temp = temp->site;
    }
    delete temp->site;
    temp->site = nullptr;
}
void readQueue(Toys*& ptr) //Чтение стека - начинаем с верхнего элемента, читаем его, затем удаляем и переходим к следующему
{
    if (ptr == nullptr) {
        return;
    }
    readQueue(ptr->site);
    cout << ptr->toy << " ";
}

//КРАСНО-ЧЕРНОЕ ДЕРЕВО
enum Color { RED, BLACK }; // 2 цвета
struct Tree //составляющие дерева
{
    int value;
    Color color;
    Tree* left;
    Tree* right;
    Tree* parent;
};
bool ifZnachTreeExist(struct Tree* root, int k) //Существует ли значение
{
    if (root == nullptr) return false;
    if (root->value == k) return true;
    if (ifZnachTreeExist(root->left, k)) return true;
    if (ifZnachTreeExist(root->right, k)) return true;
    return false;
}
Tree* CreateRoot(int k) //Создание корня
{
    Tree* root = new Tree;
    root->color = BLACK;
    root->value = k;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    return root;
}
Tree* CreateNode(int k) {// Создание нового узла (лист)
    Tree* node = new Tree;
    node->value = k;
    node->color = RED;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    return node;
}
Tree* rotateLeft(Tree*& root, Tree* x) { //Левый поворот
    Tree* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return y;
}
Tree* rotateRight(Tree*& root, Tree* y) {//Правый поворот
    Tree* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    }
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
    return x;
}
// Балансировка после вставки
void fixInsert(Tree*& root, Tree* ptr) {
    while (ptr != root && ptr->parent != nullptr && ptr->parent->color == RED) {
        Tree* parent = ptr->parent;
        Tree* grandpa = parent->parent;
        if (parent == grandpa->left) {
            Tree* uncle = grandpa->right;
            if (uncle != nullptr && uncle->color == RED) {
                // случай 1
                grandpa->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                ptr = grandpa;
            }
            else {
                if (ptr == parent->right) {
                    ptr = parent;
                    rotateLeft(root, ptr);
                    parent = ptr->parent; // обновляем parent после поворота
                }
                parent->color = BLACK;
                grandpa->color = RED;
                rotateRight(root, grandpa);
            }
        }
        else {
            Tree* uncle = grandpa->left;
            if (uncle != nullptr && uncle->color == RED) {
                // случай 1
                grandpa->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                ptr = grandpa;
            }
            else {
                if (ptr == parent->left) {
                    ptr = parent;
                    rotateRight(root, ptr);
                    parent = ptr->parent; // обновляем parent после поворота
                }
                parent->color = BLACK;
                grandpa->color = RED;
                rotateLeft(root, grandpa);
            }
        }
    }
    root->color = BLACK;
}
Tree* AddLeaf(Tree*& root, int k) { //Добавление узла
    Tree* element = CreateNode(k);
    if (root == nullptr) {
        element->color = BLACK;
        root = element;
        return root;
    }
    // Поиск места вставки
    Tree* peremElem = root;
    Tree* parent = nullptr;
    while (peremElem != nullptr) {
        parent = peremElem;
        if (k < peremElem->value)peremElem = peremElem->left;
        else peremElem = peremElem->right;
    }
    element->parent = parent;
    if (k < parent->value) parent->left = element;
    else parent->right = element;
    fixInsert(root, element);
    return root;
}
// Поиск узла по значению
Tree* findPlace(Tree* root, int k) {
    if (root == nullptr || root->value == k) return root;
    if (k < root->value)return findPlace(root->left, k);
    else return findPlace(root->right, k);
}
// Функция для замены узла
void transplant(Tree*& root, Tree* u, Tree* v) {
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}
// Балансировка после удаления
void fixDelete(Tree*& root, Tree* x, Tree* parent = nullptr) { // Добавлен параметр по умолчанию
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == nullptr) {
            // Если x nullptr, используем parent для определения стороны
            if (parent == nullptr) break; // Добавлена проверка на nullptr
            if (parent->left == nullptr) {
                x = parent->left; // все равно nullptr, но для цикла
            }
            else {
                x = parent->right;
            }
        }
        if (x == parent->left) {
            Tree* element = parent->right;
            if (element == nullptr) break;
            // Случай 1: брат красный
            if (element->color == RED) {
                element->color = BLACK;
                parent->color = RED;
                rotateLeft(root, parent);
                element = parent->right;
                if (element == nullptr) break;
            }

            // Случай 2: оба ребенка брата черные
            if ((element->left == nullptr || element->left->color == BLACK) &&
                (element->right == nullptr || element->right->color == BLACK)) {
                element->color = RED;
                x = parent;
                parent = x->parent;
            }
            else {
                // Случай 3: правый ребенок брата черный
                if (element->right == nullptr || element->right->color == BLACK) {
                    if (element->left != nullptr) {
                        element->left->color = BLACK;
                    }
                    element->color = RED;
                    rotateRight(root, element);
                    element = parent->right;
                    if (element == nullptr) break;
                }
                // Случай 4: правый ребенок брата красный
                element->color = parent->color;
                parent->color = BLACK;
                if (element->right != nullptr) {
                    element->right->color = BLACK;
                }
                rotateLeft(root, parent);
                x = root;
                break;
            }
        }
        else {
            Tree* element = parent->left;
            if (element == nullptr) break;
            // Случай 1: брат красный
            if (element->color == RED) {
                element->color = BLACK;
                parent->color = RED;
                rotateRight(root, parent);
                element = parent->left;
                if (element == nullptr) break;
            }
            // Случай 2: оба ребенка брата черные
            if ((element->right == nullptr || element->right->color == BLACK) &&
                (element->left == nullptr || element->left->color == BLACK)) {
                element->color = RED;
                x = parent;
                parent = x->parent;
            }
            else {
                // Случай 3: левый ребенок брата черный
                if (element->left == nullptr || element->left->color == BLACK) {
                    if (element->right != nullptr) {
                        element->right->color = BLACK;
                    }
                    element->color = RED;
                    rotateLeft(root, element);
                    element = parent->left;
                    if (element == nullptr) break;
                }
                // Случай 4: левый ребенок брата красный
                element->color = parent->color;
                parent->color = BLACK;
                if (element->left != nullptr) {
                    element->left->color = BLACK;
                }
                rotateRight(root, parent);
                x = root;
                break;
            }
        }
    }
    if (x != nullptr) {
        x->color = BLACK;
    }
}
// Удаление узла без детей
bool deleteLeaf(Tree*& root, int k) {
    Tree* z = findPlace(root, k);
    if (z == nullptr) {
        cout << "Узел со значением " << k << " не найден!" << endl;
        return false;
    }
    // Проверка, что узел без детей
    if (z->left != nullptr || z->right != nullptr) {
        cout << "Узел " << k << " имеет детей! Удаление невозможно." << endl;
        return false;
    }
    Tree* y = z;
    Tree* x = nullptr;
    Color y_original_color = y->color;
    if (z->left == nullptr) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        transplant(root, z, z->left);
    }
    if (y_original_color == BLACK) {
        fixDelete(root, x, z->parent); // Передаем parent
    }
    delete z;
    return true;
}
// Обход в ширину
void BFS(Tree* root) {
    if (root == nullptr) return;
    queue<Tree*> q;
    q.push(root);
    while (!q.empty()) {
        Tree* element = q.front();
        q.pop();
        cout << element->value << (element->color == RED ? "r" : "b") << " ";
        if (element->left != nullptr) q.push(element->left);
        if (element->right != nullptr) q.push(element->right);
    }
    cout << endl;
}
// Обход симметричный
void symmetrical(Tree* root) {
    if (root == nullptr) return;
    symmetrical(root->left);
    cout << root->value << (root->color == RED ? "r" : "b") << " ";
    symmetrical(root->right);
}
// Обход сверху вниз
void fromTopToBottom(Tree* root) {
    if (root == nullptr) return;
    cout << root->value << (root->color == RED ? "r" : "b") << " ";
    fromTopToBottom(root->left);
    fromTopToBottom(root->right);
}
// Обход снизу вверх
void fromBottomToTop(Tree* root) {
    if (root == nullptr) return;
    fromBottomToTop(root->left);
    fromBottomToTop(root->right);
    cout << root->value << (root->color == RED ? "r" : "b") << " ";
}
int main()
{
    setlocale(LC_ALL, "rus");
    //ДЕРЕВО
    Tree* MyTree = nullptr;
    MyTree = AddLeaf(MyTree, 15);
    MyTree = AddLeaf(MyTree, 7);
    MyTree = AddLeaf(MyTree, 11);
    MyTree = AddLeaf(MyTree, 13);
    MyTree = AddLeaf(MyTree, 9);
    MyTree = AddLeaf(MyTree, 14);
    MyTree = AddLeaf(MyTree, 20);
    MyTree = AddLeaf(MyTree, 25);
    MyTree = AddLeaf(MyTree, 26);
    MyTree = AddLeaf(MyTree, 30);
    MyTree = AddLeaf(MyTree, 35);
    deleteLeaf(MyTree, 13);
    deleteLeaf(MyTree, 11);
    BFS(MyTree);
    /*
    //Односвязный список
    Spisok* List = nullptr;
    CreateList(List, "Лунтик");
    List->place = new Spisok{ "Кузя", nullptr };
    AddChelPosle(List->place, "Корней_Корнеевич");
    AddChelDo(List, List, "Дядя_Шнюк");
    AddToEnd(List, "Мила");
    AddToBegin(List, "Бабочка");
    cout << poisk(List, "Пупсень") << endl;
    print(List);
    otherPrint(List);
    cout << endl;
    deletePoZnach(List, "Пупсень");
    deletePoZnach(List, "Мила");
    print(List);
    deleteToBegin(List);
    print(List);
    deleteToEnd(List);
    Spisok* element = FindElement(List, "Лунтик");
    deleteChelDo(List, element);
    deleteChelPosle(element);
    print(List);
    //Стек
    Garden* MyGarden = nullptr;
    addStack(MyGarden, "Груша");
    addStack(MyGarden, "Морковь");
    addStack(MyGarden, "Банан");
    readStack(MyGarden);
    cout << endl;
    deleteStack(MyGarden);//удаляем элемент
    readStack(MyGarden);
    cout << endl;
    //Очередь
    Toys* MyBox = nullptr;//Создание стеков
    addQueue(MyBox, "Юла");//Добавление в стек элемента
    addQueue(MyBox, "Кубики");
    addQueue(MyBox, "Кукла");
    addQueue(MyBox, "Лего");
    readQueue(MyBox);//выводим
    cout << endl;
    deleteQueue(MyBox);//удаляем элемент
    readQueue(MyBox);
    cout << endl;
    */
}





