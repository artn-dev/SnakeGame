#ifndef MOVE_SNAKE_COMMAND_H
#define MOVE_SNAKE_COMMAND_H

#include "TimedCommand.h"
#include "game_objects/Snake.h"


class SpeedupSnakeCommand;

class MoveSnakeCommand : public TimedCommand {

private:
        Snake *receiver_;

public:
        MoveSnakeCommand(Snake *receiver, float period)
                : TimedCommand(period), receiver_(receiver)
        {
        }

        virtual ~MoveSnakeCommand() = default;

        void execute() override
        {
                receiver_->move();
        }

        void speedup()
        {
                if (period_ > 0.1f)
                        period_ -= 0.01f;
        }

};

#endif /* MOVE_SNAKE_COMMAND_H */