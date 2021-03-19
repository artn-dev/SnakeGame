#ifndef SPEEDUP_SNAKE_COMMAND_H
#define SPEEDUP_SNAKE_COMMAND_H

#include <iostream>
#include "TimedCommand.h"
#include "MoveSnakeCommand.h"


class SpeedupSnakeCommand : public TimedCommand {

private:
        MoveSnakeCommand *receiver_;

public:
        SpeedupSnakeCommand(MoveSnakeCommand *receiver, float period)
                : TimedCommand(period), receiver_(receiver)
        {
        }

        void execute() override
        {
                receiver_->speedup();
        }

};

#endif /* SPEEDUP_SNAKE_COMMAND_H */