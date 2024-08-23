import megaognezyum

# Yeni bir RowanObject oluşturma
rowan = megaognezyum.RowanObject(domain="example.com", ip_address="192.168.1.1", data="Sensitive data")

# RowanObject bilgilerini yazdırma
rowan.print_info()  # Domain: example.com, IP Address: 192.168.1.1, Data: Sensitive data

# Veri olmadığı durum
rowan_empty = megaognezyum.RowanObject(domain="notfound.com", ip_address="192.168.1.2", data="")
rowan_empty.print_info()  # Kiwi not found
