#include "LampStateReceiver.h"

#include "shared/LampStatePubSubTypes.h"

LampStateReceiver::LampStateReceiver():
  m_domainParticipantPtr(nullptr),
  m_subscriberPtr(nullptr),
  m_topicPtr(nullptr),
  m_dataReaderPtr(nullptr),
  m_type(new LampStatePubSubType())
{
    DomainParticipantQos participantQos;
    participantQos.name("Subscriber_participant");
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
    
    if(!(m_subscriberPtr = m_domainParticipantPtr->create_subscriber(SUBSCRIBER_QOS_DEFAULT,nullptr)))
    {
        throw new std::runtime_error("Subscriber creation failed");
    }
    std::cout << "Subscriber created" << std::endl;

    if(!(m_dataReaderPtr = m_subscriberPtr->create_datareader(m_topicPtr,DATAREADER_QOS_DEFAULT,&m_listener)))
    {
        throw new std::runtime_error("Datareader creation failed");
    }
    std::cout << "Datareader created" << std::endl;
    std::cout << "Ready to receive data" << std::endl;
}

LampStateReceiver::~LampStateReceiver()
{
    if (m_dataReaderPtr)
    {
         m_subscriberPtr->delete_datareader(m_dataReaderPtr);
    }   
    if (m_subscriberPtr)
    {
        m_domainParticipantPtr->delete_subscriber(m_subscriberPtr);
    }
    if (m_topicPtr)
    {
        m_domainParticipantPtr->delete_topic(m_topicPtr);
    }
    DomainParticipantFactory::get_instance()->delete_participant(m_domainParticipantPtr);

}

void LampStateListener::on_data_available(DataReader *reader)
{
    while (reader->take_next_sample(&m_lampState,&m_sampleInfo) == ReturnCode_t::RETCODE_OK
        && m_sampleInfo.valid_data)
    {
        std::cout << "New info: Lamp " << m_lampState.LampID() << " is " << (m_lampState.on() ? "ON" : "OFF") << std::endl;
    }
    std::cout << "Done with new info" << std::endl;
}

