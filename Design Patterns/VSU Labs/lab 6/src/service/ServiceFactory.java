package service;

import dao.Transaction;
import dao.TransactionFactory;
import entity.Equipment;
import entity.Subdivision;
import exception.PersistentException;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Proxy;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ServiceFactory {
	private static final Map<Class<? extends Service>, Class<? extends Service>> SERVICES = new ConcurrentHashMap<Class<? extends Service>, Class<? extends Service>>();

	static {
		SERVICES.put(EquipmentService.class, EquipmentServiceImpl.class);
		SERVICES.put(SubdivisionService.class, SubdivisionServiceImpl.class);
		SERVICES.put(WorkingService.class, WorkingServiceImpl.class);
	}

	@SuppressWarnings("unchecked")
	public static <Type extends Service> Type getService(Class<Type> key) throws PersistentException {
		Class<? extends Service> value = SERVICES.get(key);
		if(value != null) {
			try {
				ClassLoader classLoader = value.getClassLoader();
				Class<?>[] interfaces = {key};
				Transaction transaction = TransactionFactory.createTransaction();
				Service service = value.getConstructor(Transaction.class).newInstance(transaction);
				InvocationHandler handler = new ServiceInvocationHandlerImpl(service);
				return (Type)Proxy.newProxyInstance(classLoader, interfaces, handler);
			} catch(PersistentException e) {
				throw e;
			} catch(Exception e) {
			}
		}
		return null;
	}
}
