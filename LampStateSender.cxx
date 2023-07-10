#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

#include "LampStateSender.h"

#include "shared/LampStatePubSubTypes.h"

LampStateSender::LampStateSender():
  m_domainParticipantPtr(nullptr),
  m_publisherPtr(nullptr),
  m_topicPtr(nullptr),
  m_dataWriterPtr(nullptr),
  m_type(new LampStatePubSubType())
{
    DomainParticipantQos participantQos;
    participantQos.name("Publisher_participant");
    if(!(m_domainParticipantPtr = DomainParticipantFactory::get_instance()->create_participant(0,participantQos)))
    {
        throw new std::runtime_error("Participant creation failed");
    }
    std::cout << "Participant created" << std::endl;
    m_type.register_type(m_domainParticipantPtr);
    std::cout << "Type registered" << std::endl;

    if(!(m_topicPtr = m_domainParticipantPtr->create_topic("LampStateTopic","LampState",TOPIC_QOS_DEFAULT)))
    {
        throw new std::runtime_error("Topic creation failed");
    }
    std::cout << "Topic created" << std::endl;
    
    if(!(m_publisherPtr = m_domainParticipantPtr->create_publisher(PUBLISHER_QOS_DEFAULT,nullptr)))
    {
        throw new std::runtime_error("Publisher creation failed");
    }
    std::cout << "Publisher created" << std::endl;

    if(!(m_dataWriterPtr = m_publisherPtr->create_datawriter(m_topicPtr,DATAWRITER_QOS_DEFAULT,nullptr)))
    {
        throw new std::runtime_error("Datawriter creation failed");
    }
    std::cout << "Datawriter created" << std::endl;
    std::cout << "Ready to send data" << std::endl;
}

LampStateSender::~LampStateSender()
{
    if (m_dataWriterPtr)
    {
         m_publisherPtr->delete_datawriter(m_dataWriterPtr);
    }   
    if (m_publisherPtr)
    {
        m_domainParticipantPtr->delete_publisher(m_publisherPtr);
    }
    if (m_topicPtr)
    {
        m_domainParticipantPtr->delete_topic(m_topicPtr);
    }
    DomainParticipantFactory::get_instance()->delete_participant(m_domainParticipantPtr);

}

void LampStateSender::send(LampState &lampState)
{
    m_dataWriterPtr->write(&lampState);
}

