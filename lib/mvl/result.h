/**
 * Copyright (c) 2013, Ty G. Lewis 
 * All rights reserved.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Ty G. Lewis BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _RESULT_H_
#define _RESULT_H_

#include <iostream>

namespace mvl
{
	template <class T>
	class Result
	{
		public:
			void setSuccess(bool success);
			bool getSuccess() const;

			void setMessage(const string& message);
			const string& getMessage() const;
			
			void setResult(const T& result);
			const T& getResult() const;
		private:
			bool _success;
			string _message;
			T _result;
	};

	template <class T>
	void Result<T>::setSuccess(bool success)
	{
		_success = success;
	}

	template <class T>
	bool Result<T>::getSuccess() const
	{
		return _success;
	}

	template <class T>
	void Result<T>::setMessage(const string& message)
	{
		_message = message;
	}

	template <class T>
	const string& Result<T>::getMessage() const
	{
		return _message;
	}

	template<class T>
	void Result<T>::setResult(const T& result)
	{
		_result = result;
	}

	template<class T>
	const T& Result<T>::getResult() const
	{
		return _result;
	}
}
#endif