#Submitted by:
#Balavenkat Gottimukkala (1215130189)
#Sreevashini Ravichandran (1217841794)


import OpenSSL
import cryptography
import codecs
import sys
from cryptography import x509
from cryptography.hazmat.backends import default_backend

#subject
filePath = sys.argv[3]
data = open(filePath, 'rb').read()

#p12
filePath2 = sys.argv[1]
data2 = open(filePath2, 'rb').read()

#root
filePath3 = sys.argv[2]
data3 = open(filePath3, 'rb').read()

passphrase = sys.argv[4]

cert = OpenSSL.crypto.load_certificate(OpenSSL.crypto.FILETYPE_PEM, data)
cert2 = x509.load_pem_x509_certificate(data, default_backend())

root = OpenSSL.crypto.load_certificate(OpenSSL.crypto.FILETYPE_PEM, data3)

pk12 = OpenSSL.crypto.load_pkcs12(data2, passphrase)


#Subject's Certificate verification
store = OpenSSL.crypto.X509Store()
store.add_cert(root)

storeContext = OpenSSL.crypto.X509StoreContext(store, cert)

try:
	print(storeContext.verify_certificate())
except:
	print('False')


#Subject name
for i in cert.get_subject().get_components():
	if i[0] == 'CN':
		print(i[1])


#Issuer
for i in cert.get_issuer().get_components():
	if i[0] == 'CN':
		print(i[1])
		
#Serial Number
print(cert.get_serial_number())

#Encryption algorithm
print(cert.get_signature_algorithm())

#Not Valid Before
print(cert.get_notBefore())

#Not Valid After
print(cert.get_notAfter())
print

#Public Key
pubKey = cert.get_pubkey().to_cryptography_key().public_numbers()
#Public Key Modulus (n)
print(pubKey.n)
#Public Key Exponent (e)
print(pubKey.e)
print


#Private Key Exponent (d)
privateKey = pk12.get_privatekey().to_cryptography_key().private_numbers()
print(privateKey.d)
print


#CA Public Key
pubKey2 = root.get_pubkey().to_cryptography_key().public_numbers()
#CA Public Key Modulus (n)
print(pubKey2.n)
#CA Public Key Modulus (e)
print(pubKey2.e)
print

def ByteToHex( byteStr ):    
    return ''.join( [ "%02x" % ord( x ) for x in byteStr ] ).strip()

#Hex signature of the subject's certificate
print(ByteToHex(cert2.signature))
print

public_key = cert.get_pubkey().to_cryptography_key()
private_key = pk12.get_privatekey().to_cryptography_key()

#Encryption
message = b'Hello World'
ciphertext = public_key.encrypt(message, cryptography.hazmat.primitives.asymmetric.padding.OAEP(mgf=cryptography.hazmat.primitives.asymmetric.padding.MGF1(algorithm=cryptography.hazmat.primitives.hashes.SHA256()), algorithm=cryptography.hazmat.primitives.hashes.SHA256(), label=None))

plaintext = private_key.decrypt(ciphertext, cryptography.hazmat.primitives.asymmetric.padding.OAEP(mgf=cryptography.hazmat.primitives.asymmetric.padding.MGF1(algorithm=cryptography.hazmat.primitives.hashes.SHA256()), algorithm=cryptography.hazmat.primitives.hashes.SHA256(), label=None))

#print(plaintext == message)

print(ByteToHex(ciphertext))
















