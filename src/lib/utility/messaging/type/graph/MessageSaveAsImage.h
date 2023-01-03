#ifndef MESSAGE_SAVE_AS_IMAGE_H
#define MESSAGE_SAVE_AS_IMAGE_H

#include "Message.h"


class MessageSaveAsImage: public Message<MessageSaveAsImage>
{
public:
	MessageSaveAsImage(QString path_) : path(std::move(path)) {}

	static const std::string getStaticType()
	{
		return "MessageSaveAsImage";
	}

	QString path;
};

#endif /* MESSAGE_SAVE_AS_IMAGE_H */
