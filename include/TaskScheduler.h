/*
 * Copyright (C) 2016 John M. Harris, Jr. <johnmh@openblox.org>
 *
 * This file is part of OpenBlox.
 *
 * OpenBlox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenBlox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with OpenBlox.	 If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef OB_TASKSCHEDULER
#define OB_TASKSCHEDULER

#include <vector>

#include "obtype.h"

namespace OB{
	/**
	 * This typedef describes the type of function accepted by the
	 * TaskScheduler. When queuing a task, you specify a function of
	 * this type, and any type to be used as metadata. That type is
	 * cast to a void*, which will be passed as the first parameter of
	 * this function on invocation.

	 * The return code of this function is very important, as each
	 * return code signals a different handling in the TaskScheduler.
	 * If you don't know what you're doing, just return 0 and you'll
	 * be fine. Other return codes are described here:
	 *
	 * 0 - Signals success, removes this task from the scheduler and
	 * the TaskScheduler continues processing tasks.
	 *
	 * 1 - Signals that this task either did not complete its' job or
	 * has not run yet, and that it should be left on the scheduler.
	 * The scheduler continues processing further tasks, but this task
	 * is left to be processed later.
	 *
	 * 2 - Signals success, same as a response code 0, except the
	 * TaskScheduler should stop processing tasks for this tick.
	 * 
	 * 3 - Signals that the task did not complete its' job, same as
	 * a response code 1, except the TaskScheduler should stop
	 * processing tasks for this tick.
	 */
	typedef int (*ob_task_fnc)(void* metad);

	/**
	 * This struct holds the internal data of a waiting task. This
	 * struct is not guaranteed to be the same between versions of OB,
	 * and should not be used in any code outside of libopenblox,
	 * including, but not limited to, the OpenBlox client, server and
	 * Studio software. I would go so far as to suggest that this
	 * should not be used outside of the TaskScheduler class itself,
	 * but it is exposed here for external use, if it is necessary.
	 */
	struct _ob_waiting_task{
		public:
			ob_int64 at;
			ob_int64 start;
			void* metad;
			ob_task_fnc task_fnc;
	};
	
	/**
	 * This class is used to schedule tasks to be run on the task
	 * thread, mostly tasks involving Lua states.
	 *
	 * @author John M. Harris, Jr.
	 */
	class TaskScheduler{
		public:
		    TaskScheduler();
			virtual ~TaskScheduler();

			/**
			 * Runs the task scheduler one time, handles any pending
			 * tasks and then returns. This operation can add more
			 * tasks to the queue.
			 *
			 * @author John M. Harris, Jr.
			 */
			void tick();
		private:
			std::vector<waiting_task> tasks;
	};
}

#endif // OB_TASKSCHEDULER

// Local Variables:
// mode: c++
// End:
