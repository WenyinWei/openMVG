package mq

import (
	"github.com/nsqio/go-nsq"
)

type Consumer struct {
	*nsq.Consumer
}

type Message = nsq.Message
type Handler = nsq.Handler

func NewConsumer(topic, channel, nsqdAddr string, handler Handler) (*Consumer, error) {
	cfg := nsq.NewConfig()
	c, err := nsq.NewConsumer(topic, channel, cfg)
	if err != nil {
		return nil, err
	}
	c.AddHandler(handler)
	err = c.ConnectToNSQD(nsqdAddr)
	if err != nil {
		return nil, err
	}
	return &Consumer{c}, nil
}
