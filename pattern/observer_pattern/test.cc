#include <iostream>
#include <memory> // unique_ptr
#include <list>
#include <stdexcept>

class Subject;

class Observer{
public:
    Observer(int id) { this->id_ = id;}
    virtual ~Observer() {}

    int id() {return this->id_;}

    virtual void Update() = 0;
    virtual void PrintInfo() = 0;
    virtual void Trigger() = 0;
    virtual void set_state(int state) = 0;

private:
    int id_;
};

class Subject{
public:
    Subject() {}
    virtual ~Subject() {}
    void Attach(Observer* observer) {
        this->observers_.push_back(observer);
    }
    void Dettach(Observer* observer) {
        this->observers_.remove(observer);
    }
    void Notify() {
        if (!this->observers_.size())
            throw std::out_of_range("Out of Range!\n");
        std::list<Observer *>::iterator iter;
        for(iter = this->observers_.begin(); iter != this->observers_.end(); ++iter)
            (*iter)->Update();
    }
    virtual int state() = 0;
    virtual void set_state(int state) = 0;
private:
    std::list<Observer *> observers_;
};

class ConcreteSubject : public Subject {
public:
    ConcreteSubject(): subject_state_(-1){}
    int state() {
        return this->subject_state_;
    }

    // Trigger Memeber Function
    void set_state(int state) {
        this->subject_state_ = state;
        this->Notify();
    }
private:
    int subject_state_;
};

class ConcreteObserver : public Observer{
public:
    ConcreteObserver(Subject *subject, int id): Observer(id) {
        this->subject_ = subject;
        this->subject_->Attach(this);
        this->observer_state_ = -1;
    }
    virtual ~ConcreteObserver() {
        this->subject_->Dettach(this);
    }

    void Update() {
       this->observer_state_ = this->subject_->state(); 
    }

    void PrintInfo() {
        std::cout << " > Observer #"          << this->id() << std::endl;
        std::cout << "   - subject        : " << this->subject_ << std::endl;
        std::cout << "   - observer state : " << this->observer_state_ << std::endl;
    }

    // Observer Trigger
    void Trigger() {
        this->subject_->set_state(this->observer_state_);
    }

    void set_state(int state) {
        this->observer_state_ = state;
        this->Trigger();
    }

private:
    Subject* subject_;
    int      observer_state_;
};

int
main(int agrc, char** argv)
{ 
    std::unique_ptr<Subject> subject(new ConcreteSubject);

    std::unique_ptr<Observer> observer_0(new ConcreteObserver(subject.get(), 0));
    std::unique_ptr<Observer> observer_1(new ConcreteObserver(subject.get(), 1));
    std::unique_ptr<Observer> observer_2(new ConcreteObserver(subject.get(), 2));

    try {

        // Default Status
        observer_0->PrintInfo();
        observer_1->PrintInfo();
        observer_2->PrintInfo();

        // Triggering Point
        observer_0->set_state(1);

        // Changed Status
        observer_0->PrintInfo();
        observer_1->PrintInfo();
        observer_2->PrintInfo();

    } catch (std::exception &e) {
        std::cerr << "Error : " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
