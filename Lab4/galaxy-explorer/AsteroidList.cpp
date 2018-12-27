#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
	this->data = new Asteroid(a);
}

AsteroidListItem::~AsteroidListItem() {
}

AsteroidList::AsteroidList()
{
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
    const AsteroidListItem* ptr = src.begin();
    AsteroidListItem* nptr= nullptr;
    AsteroidListItem* index = this ->beforeBegin();
    
    head.setNext(nullptr);
    
    
    while (ptr !=nullptr){
        
        index = new AsteroidListItem(ptr->getData());
        if(nptr == nullptr){
            head.setNext(index);
        }else{
            nptr->setNext(index);
        }
        
        ptr = ptr->getNext();
        nptr = index;
    }
}

AsteroidList::~AsteroidList() {
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
}

void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem* frontItem = new AsteroidListItem(e);
    AsteroidListItem* temp = this -> begin();
   
    beforeBegin()->setNext(frontItem);
    frontItem->setNext(temp); 
    //frontItem->getData() = temp->getData();
}

Asteroid& AsteroidList::front() {
	return begin()->getData();
}

const Asteroid& AsteroidList::front() const {
	return begin()->getData();
}

bool AsteroidList::isEmpty() const {
    if(beforeBegin()->getNext() == nullptr)
        return true;
    else
        return false;
}

int AsteroidList::size() const {
    const AsteroidListItem* tptr;
    int count= 0;
    for(tptr = begin(); tptr!= end(); tptr = tptr->getNext()){
        count++;
    }
    return count;
}

AsteroidListItem* AsteroidList::beforeBegin() {
    return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
    return &head;
}

AsteroidListItem* AsteroidList::begin() {
    //if(isEmpty()){
      //  return nullptr;
    //}else
        return beforeBegin()->getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
   // if(isEmpty()){
     //   return nullptr;
    //}else
        return beforeBegin()->getNext();
	
}

AsteroidListItem* AsteroidList::beforeEnd() {
    if(isEmpty()){
        return &head;
    }else{
        AsteroidListItem* tptr;
        for(tptr = begin(); tptr != end(); tptr = tptr->getNext()){
            if(tptr->getNext() == end()){
                return tptr;
        
            }
        }
       
    }
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    if(isEmpty()){
        return &head;
    }else{
        const AsteroidListItem* tptr;
        for(tptr = begin(); tptr != end(); tptr = tptr->getNext()){
            if(tptr->getNext() == end()){
                return tptr;
        
            }
        }
       
    }
}

AsteroidListItem* AsteroidList::end() {

    return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
    
    return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem* after = new AsteroidListItem(e);
    AsteroidListItem* temp = prev->getNext();
    
    prev->setNext(after);
    after->setNext(temp);
    
    return after;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    AsteroidList Others = AsteroidList(others);
    AsteroidListItem* after = Others.begin();
    AsteroidListItem* last = Others.beforeEnd();
    AsteroidListItem* temp = prev->getNext();
    
    if(after != nullptr){
        prev->setNext(after);
        last->setNext(temp);
        return last;
    }else{
        return prev;
    }
    
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    AsteroidListItem* temp = prev->getNext();
    AsteroidListItem* afterTemp = temp->getNext();
        
        if(temp == nullptr || prev == nullptr)
            return end();
        else{
            prev->setNext(afterTemp);
           
            delete temp;
            
            return afterTemp; 
        }
        
}

void AsteroidList::clear() {
    AsteroidListItem* current = begin();
    AsteroidListItem* temp;
      
    while(current != nullptr){
        temp = current;
        current = current->getNext();
        free(temp);
    }
    
    beforeBegin()->setNext(nullptr);
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    if (this == &src) return(*this);
    
    this->clear();
    
    this->insertAfter(&head, src);
    
    return (*this);
}
