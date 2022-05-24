#################################################
##          ЛАБОРАТОРНАЯ РАБОТА № 2            ##
##               БЕЛЯЕВ М.С.                   ##
##               Вариант 1                     ##
##     Предметная область - микропроцессоры    ##
#################################################

"""
  Для придания смысла цепочки рассуждений вводится ожидаемый результат:
 * Уязвимость микропроцессора (vulnerability)
"""
from prettytable import PrettyTable

##################################
######   GLOBAL VARIABLES   ######
##################################

vendor = ''            # 1. Поставщик
model = ''             # 2. Модель
command_system = ''    # 3. Система команд
clock_frequency = ''   # 4. Тактовая частота
memory_capacity = ''   # 5. Объём адресуемой памяти
existence_of_cve = ''  # 6. Существование уязвимости
bitrate = ''           # 7. Разрядность
memory_controller = '' # 8. Тип контроллера памяти
vulnerability = ''     # 9. Наименование уязвимости

fact_count = 0
facts = []
user_facts = []
rule_facts = []
#################################
#######  POSSIBLE VALUES  #######
#################################

vendor_pv = ['Qualcomm','Samsung']
model_pv = ['Snapdragon','S3C6410']
command_system_pv = ['ARMv6','ARMv7']
clock_frequency_pv = ['200/266 MHz', '1,2 GHz']
memory_capacity_pv = ['2 Gb', '4 Gb', '8 Gb']
memory_controller_pv = ['LPDDR3', 'LPDDR4']
bitrate_pv = [16, 32, 64]
existence_of_cve_pv = [True, False]
vulnerability_pv = ['CVE3031','CVE3065','CVE3066','CVE2803']
number_of_cores_pv = [4, 8, 16]

##################################
########  RW FUNCTIONS  ##########
##################################

def show(table, row, facts_row):
  table.add_row(row)
  table.add_row(facts_row)
  print(table)
  table.del_row(1)
  table.del_row(0)
  pass

def fill(row, facts_row, index, value):
  global fact_count, facts
  row[index] = value
  if facts_row[index] == '-':
    facts.append(value)
    fact_count+=1
    facts_row[index] = 'Fact ' + str(fact_count)
  pass

#################################
#####   CHEKING FUNCTIONS   #####
#################################

def vendor_check():
  global vendor, user_facts
  if vendor == '':
    print('Choose a vendor:')
    for i in range(len(vendor_pv)):
      print(f'{i + 1} - {vendor_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        vendor = vendor_pv[choice - 1]
      case 2:
        vendor = vendor_pv[choice - 1]
    user_facts.append(vendor)
  pass

def model_check():
  global model, user_facts
  if model == '':
    print('Choose a model:')
    for i in range(len(model_pv)):
      print(f'{i + 1} - {model_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        model = model_pv[choice - 1]
      case 2:
        model = model_pv[choice - 1]
    user_facts.append(model)
  pass

def command_system_check():
  global command_system, user_facts
  if command_system == '':
    print('Choose a command system:')
    for i in range(len(command_system_pv)):
      print(f'{i + 1} - {command_system_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        command_system = command_system_pv[choice - 1]
      case 2:
        command_system = command_system_pv[choice - 1]
    user_facts.append(command_system)
  pass

def clock_frequency_check():
  global clock_frequency, user_facts
  if clock_frequency == '':
    print('Choose a clock frequency:')
    for i in range(len(clock_frequency_pv)):
      print(f'{i + 1} - {clock_frequency_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        clock_frequency = clock_frequency_pv[choice - 1]
      case 2:
        clock_frequency = clock_frequency_pv[choice - 1]
    user_facts.append(clock_frequency)
  pass

def memory_capacity_check():
  global memory_capacity, user_facts
  if memory_capacity == '':
    print('Choose a memory capacity:')
    for i in range(len(memory_capacity_pv)):
      print(f'{i + 1} - {memory_capacity_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        memory_capacity = memory_capacity_pv[choice - 1]
      case 2:
        memory_capacity = memory_capacity_pv[choice - 1]
      case 3:
        memory_capacity = memory_capacity_pv[choice - 1]
    user_facts.append(memory_capacity)
  pass

def existence_of_cve_check():
  global existence_of_cve, user_facts
  if existence_of_cve == '':
    print('Choose a existence of cve:')
    for i in range(len(existence_of_cve_pv)):
      print(f'{i + 1} - {existence_of_cve_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        existence_of_cve = existence_of_cve_pv[choice - 1]
      case 2:
        existence_of_cve = existence_of_cve_pv[choice - 1]
    user_facts.append(existence_of_cve)
  pass

def bitrate_check():
  global bitrate, user_facts
  if bitrate == '':
    print('Choose a bitrate:')
    for i in range(len(bitrate_pv)):
      print(f'{i + 1} - {bitrate_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        bitrate = bitrate_pv[choice - 1]
      case 2:
        bitrate = bitrate_pv[choice - 1]
      case 3:
        bitrate = bitrate_pv[choice - 1]
    user_facts.append(bitrate)
  pass

def memory_controller_check():
  global memory_controller, user_facts
  if memory_controller == '':
    print('Choose a memory controller:')
    for i in range(len(memory_controller_pv)):
      print(f'{i + 1} - {memory_controller_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        memory_controller = memory_controller_pv[choice - 1]
      case 2:
        memory_controller = memory_controller_pv[choice - 1]
      case 3:
        memory_controller = memory_controller_pv[choice - 1]
    user_facts.append(memory_controller)
  pass

def vulnerability_check():
  global vulnerability, user_facts
  if vulnerability == '':
    print('Choose a vulnerability:')
    for i in range(len(vulnerability_pv)):
      print(f'{i + 1} - {vulnerability_pv[i]}')
    choice = int(input('-> '))
    match choice:
      case 1:
        vulnerability = vulnerability_pv[choice - 1]
      case 2:
        vulnerability = vulnerability_pv[choice - 1]
      case 3:
        vulnerability = vulnerability_pv[choice - 1]
      case 4:
        vulnerability = vulnerability_pv[choice - 1]
    user_facts.append(vulnerability)
  pass

def filling_check():
  global vendor, model,\
    command_system, memory_capacity,\
    existence_of_cve, bitrate,\
    clock_frequency, vulnerability,\
    row, facts_row
  if vendor != '':
    fill(row, facts_row, 0, vendor)
    pass
  if model != '':
    fill(row, facts_row, 1, model)
    pass
  if command_system != '':
    fill(row, facts_row, 2, command_system)
    pass
  if clock_frequency != '':
    fill(row, facts_row, 5, clock_frequency)
    pass
  if memory_capacity != '':
    fill(row, facts_row, 3, memory_capacity)
    pass
  if existence_of_cve != '':
    fill(row, facts_row, 6, existence_of_cve)
    pass
  if bitrate != '':
    fill(row, facts_row, 4, bitrate)
    pass
  if memory_controller != '':
    fill(row, facts_row, 7, memory_controller)
    pass
  if vulnerability != '':
    fill(row, facts_row, 8, vulnerability)
    pass
  show(table, row, facts_row)
  pass

#################################
###########   RULES   ###########
#################################

### RULE №1 (SIMPLE) VENDOR -> MODEL
def model_definition():
  global vendor, model
  vendor_check()
  if vendor == vendor_pv[0]:
    model = model_pv[0]
  else:
    model = model_pv[1]
  return model

### RULE №2 (COMPLEX) VENDOR + MODEL -> COMMAND SYSTEM
def command_system_definition():
  global vendor, model, command_system
  vendor_check()
  model_check()
  if vendor == vendor_pv[0] and model == model_pv[0]:
    command_system = command_system_pv[0]
  if vendor == vendor_pv[1] and model == model_pv[1]:
    command_system = command_system_pv[1]
  return command_system

### RULE №3 (SIMPLE)  COMMAND SYSTEM -> CLOCK FREQUENCY
def clock_frequency_definition():
  global command_system, clock_frequency
  command_system_check()
  if command_system == command_system_pv[0]:
    clock_frequency = '200/266 MHz'
  else:
    clock_frequency = '1,2 GHz'
  return clock_frequency

### RULE №4 (COMPLEX) MODEL + CLOCK FREQUENCY -> MEMORY CAPACITY
def memory_capacity_definition():
  global model, clock_frequency, memory_capacity
  model_check()
  clock_frequency_check()
  if model == model_pv[0] and clock_frequency == clock_frequency_pv[0]:
    memory_capacity = memory_capacity_pv[0]
  else:
    memory_capacity = memory_capacity_pv[1]
  return memory_capacity

### RULE 5 (COMPLEX) MODEL + CLOCK FREQUENCY + MEMORY CAPACITY -> CVE EXIST.
def cve_existence_definition():
  global model, clock_frequency, memory_capacity, existence_of_cve
  model_check()
  clock_frequency_check()
  memory_capacity_check()
  if model == model_pv[0] and clock_frequency == clock_frequency_pv[0] and memory_capacity == memory_capacity_pv[0]:
    existence_of_cve = False
  else:
    existence_of_cve = True
  return existence_of_cve

### RULE №6 (COMPLEX)  MODEL + CLOCK FREQUENCY -> BITRATE
def bitrate_definition():
  global model, clock_frequency, bitrate
  model_check()
  clock_frequency_check()
  if model == model_pv[0] and clock_frequency == clock_frequency_pv[0]:
      bitrate = 16
  elif model == model_pv[1] and clock_frequency == clock_frequency_pv[1]:
      bitrate = 32
  else:
      bitrate = 64
  return bitrate

### RULE 7 (COMPLEX) MODEL + MEMORY CAPACITY -> MEMORY_CONTROLLER
def memory_controller_definition():
  global model, memory_capacity, memory_controller
  model_check()
  memory_capacity_check()
  if model == model_pv[1] and memory_capacity == memory_capacity_pv[1]:
    memory_controller = memory_controller_pv[0]
  else:
    memory_controller = memory_controller_pv[1]
  return memory_controller

### RULE 8 (COMPLEX) BITRATE + MEMORY CAPACITY -> VENDOR
def vendor_definition():
  global bitrate, memory_capacity, vendor
  bitrate_check()
  memory_capacity_check()
  if bitrate == bitrate_pv[0] or bitrate_pv[1] and memory_capacity == memory_capacity_pv[0]:
    vendor = vendor_pv[0]
  else:
    vendor = vendor_pv[1]
  return vendor

### RULE 9 (COMPLEX) MODEL + CVE EXIST -> VULNERABILITY
def first_cve_definition():
  global model, existence_of_cve, vulnerability
  model_check()
  existence_of_cve_check()
  if model == model_pv[0] and existence_of_cve == True:
    vulnerability = vulnerability_pv[0]
  elif model == model_pv[1] and existence_of_cve == True:
    vulnerability = vulnerability_pv[1]
  else:
    vulnerability = vulnerability_pv[0]
  return vulnerability

### RULE 10 (COMPLEX) BITRATE + CVE EXIST -> VULNERABILITY
def second_cve_definition():
  global bitrate, existence_of_cve, vulnerability
  bitrate_check()
  existence_of_cve_check()
  if bitrate == bitrate_pv[0] and existence_of_cve == True:
    vulnerability = vulnerability_pv[1]
  elif bitrate == bitrate_pv[1] and existence_of_cve == True:
    vulnerability = vulnerability_pv[2]
  else:
    vulnerability = vulnerability_pv[1]
  return vulnerability

### RULE 11 (COMPLEX) BITRATE + CLOCK FREQUENCY + MEMORY CAPACITY -> VULNERABILITY
def third_cve_definition():
  global bitrate, clock_frequency, memory_capacity, vulnerability
  bitrate_check()
  clock_frequency_check()
  memory_capacity_check()
  if bitrate == bitrate_pv[0] and clock_frequency == clock_frequency_pv[1]:
    vulnerability = vulnerability_pv[3]
  else:
    vulnerability = vulnerability_pv[2]
  return vulnerability

### RULE 12 (COMPLEX) CLOCK FREQUENCY + MEMORY_CONTROLLER -> VULNERABILITY
def fourth_cve_definition():
  global clock_frequency, memory_controller, vulnerability
  clock_frequency_check()
  memory_controller_check()
  if clock_frequency == clock_frequency_pv[1] and memory_controller == memory_controller_pv[0]:
    vulnerability = vulnerability_pv[3]
  elif clock_frequency == clock_frequency_pv[0]:
    vulnerability = vulnerability_pv[0]
  else:
    vulnerability = vulnerability_pv[3]
  return vulnerability
#################################
##########  EXECUTION  ##########
#################################

if __name__ == '__main__':
  # Определение заголовка таблицы
  title = ['VENDOR','MODEL','COMMAND SYS.','MEMORY CAP.','BITRATE','FREQUENCY','CVE EXIST.','MEMORY CONTR.', 'CVE']
  row = ['-','-','-','-','-','-','-','-','-']
  facts_row = ['-', '-', '-', '-', '-', '-', '-','-', '-']
  table = PrettyTable(title)  # Определение таблицы
  show(table,row,facts_row)

  print('\n1 - Direct chain of reasosing\n2 - Reverse chain of reasosning')
  method = input('\nChoose chain of reasoning: ')

  if method == '1':
    #################################
    ##  DIRECT CHAIN OF REASONING  ##
    #################################
    how_many = int(input('\nHow many facts are known?\n-> '))
    for i in range(how_many):
      the_fact = input('\tChoose a fact:'\
                       '\n1 - Vendor'\
                       '\n2 - Model'\
                       '\n3 - Comand system'\
                       '\n4 - Memory capacity'\
                       '\n5 - Bitrate'\
                       '\n6 - Frequency'\
                       '\n7 - CVE exists'\
                       '\n8 - Memory controller'\
                       '\n9 - CVE\n -> ')
      match the_fact: # Выбор факта
        case '1':
          vendor_check()
          filling_check()
        case '2':
          model_check()
          filling_check()
        case '3':
          command_system_check()
          filling_check()
        case '4':
          memory_capacity_check()
          filling_check()
        case '5':
          bitrate_check()
          filling_check()
        case '6':
          clock_frequency_check()
          filling_check()
        case '7':
          existence_of_cve_check()
          filling_check()
        case '8':
          memory_controller_check()
          filling_check()
        case '9':
          vulnerability_check()
          filling_check()
        case _:
          pass
    while fact_count != 9:
      ########### CALL RULE №1 (SIMPLE) VENDOR -> MODEL
      if model == '' and vendor != '':
        result = model_definition()
        rule_facts.append(result)
        print('\nRULE 1: vendor -> model')
        filling_check()
      ########### CALL RULE №2 (COMPLEX) VENDOR + MODEL -> COMMAND SYSTEM
      if command_system == '' and vendor != '':
        result = command_system_definition()
        rule_facts.append(result)
        print('\nRULE 2: vendor, model -> command system')
        filling_check()
      ########### CALL RULE №3 (SIMPLE)  COMMAND SYSTEM -> CLOCK FREQUENCY
      if clock_frequency == '' and bitrate != '':
        result = clock_frequency_definition()
        rule_facts.append(result)
        print('\nRULE 3: command system -> clock frequency')
        filling_check()
      ########### CALL RULE №4 (COMPLEX) MODEL + CLOCK FREQUENCY -> MEMORY CAPACITY
      if memory_capacity == '':
        result = memory_capacity_definition()
        rule_facts.append(result)
        print('\nRULE 4: model, clock frequency -> memory capacity')
        filling_check()
      ########### CALL RULE 5 (COMPLEX) MODEL + CLOCK FREQUENCY + MEMORY CAPACITY -> CVE EXIST.
      if existence_of_cve == '' and vendor == '':
        result = cve_existence_definition()
        rule_facts.append(result)
        print('\nRULE 5: model, clock frequency, memory capacity -> cve exist.')
        filling_check()
      ########### CALL RULE №6 (COMPLEX)  MODEL + CLOCK FREQUENCY -> BITRATE
      if bitrate == '':
        result = bitrate_definition()
        rule_facts.append(result)
        print('\nRULE 6: model, clock frequency -> bitrate')
        filling_check()
      ########### CALL RULE 7 (COMPLEX) BITRATE + MEMORY CAPACITY -> VENDOR
      if vendor == '' and clock_frequency != '':
        result = vendor_definition()
        rule_facts.append(result)
        print('\nRULE 7: bitrate, memory capacity -> vendor')
        filling_check()
      ########### CALL RULE 8 (COMPLEX) MODEL + MEMORY CAPACITY -> MEMORY_CONTROLLER
      if memory_controller == '':
        result = memory_controller_definition()
        rule_facts.append(result)
        print('\nRULE 8: model, memory capacity -> memory controller')
        filling_check()
      ########### CALL RULE 9 (COMPLEX) MODEL + CVE EXIST -> VULNERABILITY
      if vulnerability == '' and model != '':
        result = first_cve_definition()
        rule_facts.append(result)
        print('\nRULE 9: model, cve exist. -> vulnerability')
        filling_check()
      ########### CALL RULE 10 (COMPLEX) BITRATE + CVE EXIST -> VULNERABILITY
      if vulnerability == '' and bitrate != '':
        result = second_cve_definition()
        rule_facts.append(result)
        print('\nRULE 10: bitrate, cve exist. -> vulnerability')
        filling_check()
      ########### CALL RULE 11 (COMPLEX) BITRATE + CLOCK FREQUENCY + MEMORY CAPACITY -> VULNERABILITY
      if vulnerability == '' and vendor != '':
        result = third_cve_definition()
        rule_facts.append(result)
        print('\nRULE 11: bitrate, clock frequency, memory capacity -> vulnerability')
        filling_check()
      ########### CALL RULE 12 (COMPLEX) CLOCK FREQUENCY + MEMORY_CONTROLLER -> VULNERABILITY
      if vulnerability == '' and existence_of_cve != '':
        result = fourth_cve_definition()
        rule_facts.append(result)
        print('\nRULE 12: clock frequency, memory controller -> vulnerability')
        filling_check()
    print('USER FACTS: ', user_facts)
    print('RULE FACTS: ', rule_facts)
  else:
    ##################################
    ##  REVERSE CHAIN OF REASONING  ##
    ##################################
    the_fact = input('Choose a vulnerability:\n1 - CVE3031\n2 - CVE3065\n3 - CVE3066\n4 - CVE2803\n-> ')

    match the_fact:
      case '1':
        vulnerability = vulnerability_pv[0]
        user_facts.append(vulnerability)
        filling_check()
      case '2':
        vulnerability = vulnerability_pv[1]
        user_facts.append(vulnerability)
        filling_check()
      case '3':
        vulnerability = vulnerability_pv[2]
        user_facts.append(vulnerability)
        filling_check()
      case '4':
        vulnerability = vulnerability_pv[3]
        user_facts.append(vulnerability)
        filling_check()
      case _:
        pass

    while fact_count != 9:
      if model == '' and existence_of_cve == '':
        model_definition()
        filling_check()
      if bitrate == '' and existence_of_cve == '':
        bitrate_definition()
        filling_check()
      if bitrate != '' and clock_frequency == '' and memory_capacity != '':
        bitrate_definition()
        filling_check()
      if clock_frequency == '' and memory_controller == '':
        clock_frequency_definition()
        filling_check()
      if command_system == '':
        command_system_definition()
        filling_check()
      if memory_controller == '':
        memory_controller_definition()
        filling_check()
      if vulnerability != '':
        existence_of_cve = 'True'
        filling_check()

    for i in facts:
      if i not in user_facts:
        rule_facts.append(i)

    print('USER FACTS: ', user_facts)
    print('RULE FACTS: ', rule_facts)



