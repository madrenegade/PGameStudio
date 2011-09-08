/* 
 * File:   ChangeListener.h
 * Author: madrenegade
 *
 * Created on September 7, 2011, 11:31 AM
 */

#ifndef MEMPROF_CHANGELISTENER_H
#define MEMPROF_CHANGELISTENER_H



namespace memprof
{
    class sample;

    class change_listener
    {
    public:

        ~change_listener()
        {
        };

        virtual void on_new_frame() = 0;
        virtual void on_allocation(const sample& sample) = 0;

    protected:

        change_listener()
        {
        };
    };
}

#endif	/* MEMPROF_CHANGELISTENER_H */

