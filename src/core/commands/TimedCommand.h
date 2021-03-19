#ifndef TIMED_COMMAND_H
#define TIMED_COMMAND_H

class TimedCommand {

protected:
        float period_;
        float counter;

public:
        TimedCommand(float period) : period_(period) { }

        virtual ~TimedCommand() = default;

        void execute(float delta_time)
        {
                counter += delta_time;

                if (counter >= period_) {
                        execute();
                        counter = 0.0f;
                }
        }

        virtual void execute() = 0;

};

#endif /* TIMED_COMMAND_H */