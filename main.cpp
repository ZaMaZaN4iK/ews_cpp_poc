#include <ews/ews.hpp>

#include <exception>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    ews::set_up();

    try {
        const auto basicCreds = ews::oauth2_credentials("qa@inovwave1.onmicrosoft.com");

        auto service = ews::service("https://outlook.office365.com/ews/Exchange.asmx",
                                    basicCreds);
        ews::connecting_sid imp(ews::connecting_sid::type::primary_smtp_address, "qa@inovwave1.onmicrosoft.com");
        service.impersonate(imp);

        auto search_expression =
                ews::contains(ews::item_property_path::subject, "150 MB",
                              ews::containment_mode::substring,
                              ews::containment_comparison::ignore_case);

        ews::distinguished_folder_id inbox = ews::standard_folder::inbox;
        auto items = service.find_item(inbox, search_expression);

        for(const auto& item : items)
        {
            auto message = service.get_message(item);
            auto attachments = message.get_attachments();
            std::cout << attachments.back().id().to_xml() << std::endl;

            /*for(const auto& attachment : attachments)
            {*/
                //std::cout << attachments.back().content() << std::endl;
                std::fstream attachment_file;
                attachment_file.open("/home/zamazan4ik/OpenSource/ews_cpp_poc/attach_new.txt", std::ios_base::out);

                auto attachment = service.get_attachment(attachments.back().id());
                attachment_file << service.get_attachment(attachments.back().id()).content();
                attachment_file.close();

                //auto new_attach = ews::attachment();
                //auto new_attach = ews::attachment::from_file("/home/zamazan4ik/OpenSource/ews_cpp_poc/decoded.txt", "text", "log.txt");
                //service.create_attachment(message.get_item_id(), new_attach);
            //}

        }

        /*auto message = ews::message();
        message.set_subject("Test mail from outer space");
        std::vector<ews::mailbox> recipients{ ews::mailbox("qa@inovwave1.onmicrosoft.com") };
        message.set_to_recipients(recipients);
        auto text = ews::body("ようこそ (Welcome!)\n\nThis is a test.\n");
        message.set_body(text);
        service.create_item(message, ews::message_disposition::send_and_save_copy);*/
    } catch (std::exception& exc) {
        std::cout << exc.what() << std::endl;
    }

    ews::tear_down();
    return 0;
}
