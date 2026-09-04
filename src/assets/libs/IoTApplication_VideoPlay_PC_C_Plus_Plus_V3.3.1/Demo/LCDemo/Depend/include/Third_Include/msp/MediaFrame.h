
#ifndef _MEDIA_FRAME_H_
#define _MEDIA_FRAME_H_

class MediaFrame
{
public:
	MediaFrame();
	virtual ~MediaFrame();

	char *GetFrameBuffer();
	int GetFrameLength() const;

private:
	friend class RtpPacketManager;
	friend class PgStreamParser;
	int AllocBuffer(int nLen);	

private:
	char *m_pBuff;
	int m_nLen;
};

inline char *MediaFrame::GetFrameBuffer()
{
	return m_pBuff;
}

inline int MediaFrame::GetFrameLength() const
{
	return m_nLen;
}

#endif
