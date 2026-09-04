
#ifndef __COMSELECTOR_LOCAL_COMSELECT_MANAGER_H__
#define __COMSELECTOR_LOCAL_COMSELECT_MANAGER_H__
#include "Defs.h"
#include "Infra/String.h"


namespace Dahua{
namespace Component{

class CLocalComSelectManager
{
public:
	/// 设置默认组件classid (只允许设置一次)
	/// \param [in] 组件的 iid
	/// \param [in] 组件的 默认的classid
	COMPONENT_API static bool setDefaultComponent(const char* iid, const char* clsid);

	/// 获取默认组件classid
	/// \param [in] 组件的 iid
	/// \return [out] 组件的 默认的classid或者classid.subclassID，如果iid不存在，返回空字符串""
	COMPONENT_API static Dahua::Infra::CString getDefaultClassID(const char* iid);
	
};

}
}

#endif

