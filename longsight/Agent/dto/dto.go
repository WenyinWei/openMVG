package dto

import "strconv"

const (
	ChannelServer = "Server"
	ChannelClient = "Client"

	TopicToServer = "ToServer"
	TopicToClient = "ToClient"
)

func MakeChannelClient(id int) string {
	return ChannelClient + strconv.Itoa(id)
}

type Type int

const (
	TypeCapture         Type = 1
	TypeCaptureCallback Type = 2
)

type CaptureMessage struct {
	Id int
}

type CaptureCallbackMessage struct {
	Id       int
	Filename string
	Url      string
}
