//
// Created by Mocan Luiza on 5/29/2025.
//

#ifndef UNDOACTION_H
#define UNDOACTION_H
#include "Controller.h"
#include "Dog.h"


class UndoAction {
public:
    virtual void undo()=0;
    virtual void redo()=0;
    virtual ~UndoAction()=default;
};

class UndoAdd: public UndoAction {
private:
    Controller& controller;
    Dog dog;
    public:
    UndoAdd(Controller& ctrl, const Dog &dog):controller(ctrl),dog(dog){}
    void undo() override{controller.removeAdminRaw(dog);}
    void redo() override{controller.addAdminRaw(dog);}
};

class UndoRemove: public UndoAction {
private:
    Controller& controller;
    Dog dog;
    public:
    UndoRemove(Controller& ctrl, const Dog &dog):controller(ctrl),dog(dog){}
    void undo() override{controller.addAdminRaw(dog);}
    void redo() override{controller.removeAdminRaw(dog);}
};


class UndoUpdate: public UndoAction {
private:
    Controller& controller;
    Dog old_dog, new_dog;

public:
    UndoUpdate(Controller& ctrl, const Dog& oldDog, const Dog& newDog)
        : controller(ctrl), old_dog(oldDog), new_dog(newDog) {}

    void undo() override { controller.updateAdminRaw(new_dog, old_dog); }
    void redo() override { controller.updateAdminRaw(old_dog, new_dog); }
};

#endif //UNDOACTION_H
