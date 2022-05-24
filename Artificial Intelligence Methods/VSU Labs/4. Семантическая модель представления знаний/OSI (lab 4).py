#################################################
##          ЛАБОРАТОРНАЯ РАБОТА № 4            ##
##               БЕЛЯЕВ М.С.                   ##
##               Вариант 1                     ##
##    Предметная область - компьютерные сети   ##
#################################################

from prettytable import PrettyTable
import sys

select_list = [] # Список выбираемых объектов
object = ''
object_index = 0
"""
#
#   Данная семантическая сеть осуществляет поиск и их свойств объектов согласно предметной области
#
"""

class OSI:
  name = 'Сетевая модель (стек сетевых протоколов OSI/ISO).'
  protocol_list = ['HTTP','SMTP','DNS','FTP','MIME', 'SSL','RPC', 'PAP','L2TP','gRPC','TCP','UDP','SCTP','Ports',
                   'IPv4','IPv6','IPsec','AppleTalk','ICMP','PPP','IEEE 802.22','Ethernet','DSL','ARP','NIC.','USB','RJ']

  def whoami(self):
    print(self.name)
    pass
  def view_layer_info(self, layer):
    layer.whoami()
    pass
  def show_structure(self):
    title = ['DATA TYPES', 'LAYER', 'PROTOCOL']
    rows = [ [' ', 'Application', 'HTTP, SMTP, DNS, FTP...'],
             ['Data', 'Presentation', 'MIME, SSL...'],
             [' ', 'Session', 'NetBIOS, SOCKS,ADSP, ASP, ISO-SP, L2TP...'],
             ['Segment','Transport','TCP, UDP, SCTP, DCCP, Ports...'],
             ['Package','Network','IPv4, IPv6, IPsec, AppleTalk, ICMP...'],
             ['Frame','Data link','PPP, IEEE 802.22, Ethernet, DSL, ARP, NIC...'],
             ['Bit','Physical','USB, RJ...']]
    table = PrettyTable(title)
    for r in rows:
        table.add_row(r)
        table.add_row(['-','-','-'])
    print(table)
    pass
  def purpose(self):
    print('\nПредназначена для описания взаимодействия сетевых уровней.',
          '\nЯвляется теоретической моделью организации сети. Разработана в конце 1970-х')
    pass
  def protocols(self):
    print('Протоколы:')
    for p in self.protocol_list:
      print(' * '+p)
    pass
  def parent(self):
    print('International Organization for Standardization')

class Application(OSI):
  name = 'Прикладной уровень'
  protocol_list = ['HTTP','SMTP','DNS','FTP']

  def whoami(self):
    print(self.name)
    pass
  def purpose(self):
    print('\nРешает задачи взаимодействия приложений.',
          '\nФормирует запросы к уровню представления.')
    pass
  def protocols(self):
    print('Протоколы:')
    for p in self.protocol_list:
      print(' * '+p)
    pass
  def parent(self):
    print(OSI.name)
    pass
  def child(self):
    print(Presentation.name)
    pass

class Presentation(OSI):
  name = 'Уровень представлений.'
  protocol_list = ['MIME','SSL']

  def whoami(self):
    print(self.name)
    pass
  def purpose(self):
    print('\nПредставляет данные в понятном человеку и машине виде.',
          '\nНапример, когда одно устройство умеет отображать текст только в кодировке ASCII, а другое только в UTF-8,'
          ' перевод текста из одной кодировки в другую происходит на шестом уровне..\n')
    pass
  def protocols(self):
    print('Протоколы:')
    for p in self.protocol_list:
      print(' * '+p)
    pass
  def parent(self):
    print(Application.name)
    pass
  def child(self):
    print(Session.name)
    pass

class Session(OSI):
  name = 'Сеансовый уровень.'
  protocol_list = ['RPC','PAP','L2TP','gRPC']

  def whoami(self):
    print(self.name)
    pass
  def purpose(self):
    print('\nОтвечает за поддержку сеанса или сессии связи..',
          '\nПримером работы пятого уровня может служить видеозвонок по сети. '
          '\nВо время видеосвязи необходимо, чтобы два потока данных (аудио и видео) шли синхронно. '
          '\nКогда к разговору двоих человек прибавится третий — получится уже конференция.'
          '\nЗадача пятого уровня — сделать так, чтобы собеседники могли понять, кто сейчас говорит..\n')
    pass
  def protocols(self):
    print('Протоколы:')
    for p in self.protocol_list:
      print(' * '+p)
    pass
  def parent(self):
    print(Presentation.name)
    pass
  def child(self):
    print(Transport.name)
    pass

class Transport(OSI):
  name = 'Транспортный уровень.'
  protocol_list = ['TCP','UDP','SCTP','Ports']

  def whoami(self):
    print(self.name)
    pass
  def purpose(self):
    print('\nПредназначен для доставки данных. '
          '\nПри этом неважно, какие данные передаются, откуда и куда, то есть, он предоставляет сам механизм '
          'передачи. '
          '\nБлоки данных он разделяет на фрагменты, размеры которых зависят от протокола: короткие объединяет в '
          'один, а длинные разбивает\n')
    pass
  def protocols(self):
    print('Протоколы:')
    for p in self.protocol_list:
      print(' * '+p)
    pass
  def parent(self):
    print(Session.name)
    pass
  def child(self):
    print(Network.name)
    pass

class Network(OSI):
  name = 'Сетевой уровень.'
  protocol_list = ['IPv4','IPv6','IPsec','AppleTalk','ICMP']

  def whoami(self):
    print(self.name)
    pass
  def purpose(self):
    print('\nПредназначается для определения пути передачи данных.'
          '\nОтвечает за трансляцию логических адресов и имён в физические, определение кратчайших маршрутов, коммутацию и маршрутизацию, отслеживание неполадок и заторов в сети.'
          '\nНа этом уровне работает такое сетевое устройство, как маршрутизатор.\n')
    pass
  def protocols(self):
    print('Протоколы:')
    for p in self.protocol_list:
      print(' * '+p)
    pass
  def parent(self):
    print(Transport.name)
    pass
  def child(self):
    print(DataLink.name)
    pass

class DataLink(OSI):
  name = 'Канальный уровень.'
  protocol_list = ['PPP','IEEE 802.22','Ethernet','DSL','ARP','NIC.']

  def whoami(self):
    print(self.name)
    pass
  def purpose(self):
    print('\nПредназначен для передачи данных узлам, находящимся в том же сегменте локальной сети.'
          '\nТакже может использоваться для обнаружения и, возможно, исправления ошибок, возникших на физическом '
          'уровне.\n')
    pass
  def protocols(self):
    print('Протоколы:')
    for p in self.protocol_list:
      print(' * '+p)
    pass
  def parent(self):
    print(Network.name)
    pass
  def child(self):
    print(Physical.name)
    pass

class Physical(OSI):
  name = 'Физический уровень.'
  protocol_list = ['USB','RJ']

  def whoami(self):
    print(self.name)
    pass
  def purpose(self):
    print('\nОписывает способы передачи бит (а не пакетов данных) через физические среды линий связи, соединяющие '
          'сетевые устройства. '
          '\nНа этом уровне описываются параметры сигналов, такие как амплитуда, частота, фаза, используемая '
          'модуляция, манипуляция.'
          '\nРешаются вопросы, связанные с синхронизацией, избавлением от помех, скоростью передачи данных.\n')
    pass
  def protocols(self):
    print('Протоколы:')
    for p in self.protocol_list:
      print(' * '+p)
    pass
  def parent(self):
    print(DataLink.name)
    pass
  def child(self):
    print(None)
    pass

class Protocol(OSI):
  name = ''
  protolol_list = OSI.protocol_list

  def whoami(self):
    print(self.name)
    pass
  def purpose(self):
    print('\nОписывает взаимодействие объектов сети.\n')
    pass
  def protocols(self):
    print('Протокол не содержит протоколов :)')
    pass
  def parent(self):
    if self.name in Application.protocol_list:
      print(f'{Application.name}.')
    if self.name in Presentation.protocol_list:
      print(f'{Presentation.name}.')
    if self.name in Session.protocol_list:
      print(f'{Session.name}.')
    if self.name in Transport.protocol_list:
      print(f'{Transport.name}.')
    if self.name in Network.protocol_list:
      print(f'{Network.name}.')
    if self.name in DataLink.protocol_list:
      print(f'{DataLink.name}.')
    if self.name in Physical.protocol_list:
      print(f'{Physical.name}.')
    pass
  def child(self):
    print(None)
    pass


def search(object_name):
  global select_list, object_index
  find = False

  model = OSI()
  layer7 = Application()
  layer6 = Presentation()
  layer5 = Session()
  layer4 = Transport()
  layer3 = Network()
  layer2 = DataLink()
  layer1 = Physical()
  protocol = Protocol()

  if object_name in model.name.lower():
    object_index +=1
    print(str(object_index) +'. '+model.name)
    select_list.append(model)
    find = True
  if object_name in layer7.name.lower():
    object_index +=1
    print(str(object_index) +'. '+layer7.name)
    select_list.append(layer7)
    find = True
  if object_name in layer6.name.lower():
    object_index +=1
    print(str(object_index) +'. '+layer6.name)
    select_list.append(layer6)
    find = True
  if object_name in layer5.name.lower():
    object_index +=1
    print(str(object_index) +'. '+layer5.name)
    select_list.append(layer5)
    find = True
  if object_name in layer4.name.lower():
    object_index +=1
    print(str(object_index) +'. '+layer4.name)
    select_list.append(layer4)
    find = True
  if object_name in layer3.name.lower():
    object_index +=1
    print(str(object_index) +'. '+layer3.name)
    select_list.append(layer3)
    find = True
  if object_name in layer2.name.lower():
    object_index +=1
    print(str(object_index) +'. '+layer2.name)
    select_list.append(layer2)
    find = True
  if object_name in layer1.name.lower():
    object_index +=1
    print(str(object_index) +'. '+layer1.name)
    select_list.append(layer1)
    find = True
  for p_name in protocol.protocol_list:
    if object_name in p_name.lower():
      object_index += 1
      print(str(object_index) + '. ' + p_name)
      protocol.name = p_name
      select_list.append(protocol)
      find = True
  if find == False:
    print('Объект не найден!')
    sys.exit()
  pass

def select():
  global object
  key = input('Выберите объект: ')
  match key:
    case '1':
      object = select_list[0]
    case '2':
      object = select_list[1]
    case '3':
      object = select_list[2]
    case '4':
      object = select_list[3]
    case '5':
      object = select_list[4]
    case '6':
      object = select_list[5]
    case '7':
      object = select_list[6]
    case '8':
      object = select_list[7]
    case '9':
      object = select_list[8]
    case '10':
      object = select_list[9]
    case '11':
      object = select_list[10]
    case '12':
      object = select_list[11]
    case '13':
      object = select_list[12]
    case _:
      print('Индекс не найден')
      pass
  actions()
  pass

def actions():
  global object
  second_key = input('\tВыберите действие:'
                     '\n1 - Отобразить назначение:'
                     '\n2 - Вывести список протоколов'
                     '\n3 - Отобразить родителя'
                     '\n4 - Отобразить потомка\n-> ')
  match second_key:
    case '1':
      object.purpose()
    case '2':
      object.protocols()
    case '3':
      object.parent()
    case '4':
      object.child()
    case _:
      print('Неизвестное действие')
  pass

if __name__ == '__main__':

  #p = Protocol()
  #print(p.name)
  key = input('\tВыберите действие:'\
                         '\n1 - Поиск объекта'\
                         '\n2 - Показать иерархию\n-> ')
  match key:
    case '1':
      object_name = input('Введите название объекта: ')
      search(object_name)
      select()
    case '2':
      model = OSI()
      model.show_structure()
    case _:
      sys.exit()