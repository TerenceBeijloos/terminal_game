#include "Frame.h"
#include "GCElement.h"

template <class Storage_type, class Frame_type>
class IAssembler : public GCElement
{
protected:
	IAssembler() {};

public:
	static  IAssembler* instance();
public:
	virtual ~IAssembler() {};

	virtual void add(Frame_type& frame, const Position& pos, const Pixel& priority) {};

private:
	static IAssembler* m_Instance;
};
