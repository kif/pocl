/* OpenCL runtime library: clGetPlatformInfo()

   Copyright (c) 2011 Kalle Raiskila 
   
   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <string.h>
#include "pocl_cl.h"

CL_API_ENTRY cl_int CL_API_CALL 
clGetPlatformInfo(cl_platform_id   platform,
                  cl_platform_info param_name,
                  size_t           param_value_size, 
                  void *           param_value,
                  size_t *         param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
  const char *ret;
  int retlen;

  if (platform == NULL || (platform->magic != 42))
    return CL_INVALID_PLATFORM;
	
  switch (param_name)
  {
    case CL_PLATFORM_PROFILE:
      // TODO: figure this out depending on the native execution host.
      // assume FULL_PROFILE for now.
      ret = "FULL_PROFILE";
      break;
    case CL_PLATFORM_VERSION:
      ret = "OpenCL 1.2";
      break;
    case CL_PLATFORM_NAME:
      ret = "Portable OpenCL";
      break;
    case CL_PLATFORM_VENDOR:
      ret = "The POCL project";
      break;
    case CL_PLATFORM_EXTENSIONS:
      // TODO: list all suppoted extensions here.
      ret = "";
      break;
    default: 
      return CL_INVALID_VALUE;
  }

  // the OpenCL API docs *seem* to count the trailing NULL
  retlen = strlen(ret) + 1;
	
  if (param_value != NULL)
  {
    if (param_value_size < retlen)
      return CL_INVALID_VALUE;
    
    strncpy(param_value, ret, retlen); 
  }
	
  if (param_value_size_ret != NULL)
    *param_value_size_ret = retlen;
	
  return CL_SUCCESS;
}
