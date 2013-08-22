#ifndef _VAR_LENGTH_VECTOR_INTERFACE_H_
#define _VAR_LENGTH_VECTOR_INTERFACE_H_

#include "vector_interface.h"

namespace mvl
{
	template<class T>
	class IVarLengthVector: public IVector<T>
	{
	public:
		virtual ~IVarLengthVector() {}

		/**
		 * Resizes the dimension of the vector. If the vector
		 * has more dimensions than the the new dimension, the
		 * higher dimension values are sliced off while lower dimensions
		 * are preserved.
		 * @param column
		 * @return 
		 */
		virtual void setDimension(unsigned int dimension) = 0;

		/**
		 * Sets the components of the vector
		 * @return 
		 */
		virtual void setComponents(const T* components, unsigned int len) = 0;

		/**
		 * Clear entries and sets dimension to 0
		 * @param components
		 * @param len
		 */
		virtual void clear() = 0;
	};
}

#endif